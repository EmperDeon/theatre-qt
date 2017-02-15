#include "TFileUpload.h"
#include "TDB.h"

TFileUpload::TFileUpload(QString u) : url(u) {
	QHBoxLayout *l = new QHBoxLayout;

	l_img = new QLabel;
	QPushButton *b_upload = new QPushButton("Загрузить изображение");

	connect(b_upload, &QPushButton::clicked, this, &TFileUpload::upload);

	l->addWidget(l_img);
	l->addWidget(b_upload);

	setLayout(l);
}

void TFileUpload::upload() {
	QString file = QFileDialog::getOpenFileName(this, "Загрузка изображения", "", "Изображения (*.png *.jpg)");

	QPixmap i(file);
	if (i.width() > 2000 || i.height() > 2000)
		QMessageBox::warning(this, "Внимание",
		                     "Размер файла больше чем 2000 пикселей по ширине или высоте \nПроцесс преобразования может занять более 30 секунд");


	// First image - original
	i = i.scaledToHeight(1000, Qt::SmoothTransformation);

	QByteArray *bytes = new QByteArray;
	QBuffer *io1 = new QBuffer(bytes);
	io1->open(QIODevice::WriteOnly);

	i.save(io1, "PNG");

	io1->close();
	io1->open(QIODevice::ReadOnly);
	// First image - original


	// Second image - preview
	i = i.scaledToHeight(200, Qt::SmoothTransformation);

	QByteArray *bytes2 = new QByteArray;
	QBuffer *io2 = new QBuffer(bytes2);
	io2->open(QIODevice::WriteOnly);

	i.save(io2, "PNG");

	io2->close();
	io2->open(QIODevice::ReadOnly);
	// Second image - preview

	l_img->setPixmap(i);

	url = TDB().upload({{"img",     io1},
	                    {"preview", io2}}).toString();
}

QPixmap TFileUpload::getPreview(QString u) {
	if (u != "none") {
		QJsonValue v = TDB().request("utils/preview", {{"url", u}});
		return getImage(v);

	} else {
		return QPixmap(":/none.png");
	}
}

QPixmap TFileUpload::getImage(QJsonValue p) {
	QPixmap i;

	i.loadFromData(QByteArray::fromBase64(p.toString().toUtf8()));

	if (i.height() > 200)
		i = i.scaledToHeight(200, Qt::SmoothTransformation);
	else if (i.height() == 0)
		i = QPixmap(":/none.png");

	return i;
}

void TFileUpload::load(QString u) {
	url = u;

	QTimer::singleShot(100, [=]() {
		l_img->setPixmap(getPreview(url));
	});
}

QString TFileUpload::getUrl() const {
	if (url == "")
		return "none.png";

	return url;
}

void TFileUpload::clear() {
	l_img->clear();
	url = "";
}
