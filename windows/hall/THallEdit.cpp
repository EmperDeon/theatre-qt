#include "THallEdit.h"
#include <utils/TDB.h>

THallEdit::THallEdit() {
	QVBoxLayout *l = new QVBoxLayout;
	hall = new THall();
	hall->clear();

	// Size - Top menu
	QHBoxLayout *tl = new QHBoxLayout;

	QPushButton *b_crop = new QPushButton("Обрезать"), *b_size = new QPushButton("Изменить размер");
	l_h_w = new QLineEdit;
	l_h_h = new QLineEdit;
	l_h_n = new QLineEdit;
	QLabel *t_h_w = new QLabel("Ширина:"), *t_h_h = new QLabel("Высота:"), *t_h_n = new QLabel("Название:");

	l_h_w->setValidator(new QIntValidator(1, 200));
	l_h_h->setValidator(new QIntValidator(1, 200));
	t_h_w->setBuddy(l_h_w);
	t_h_h->setBuddy(l_h_h);
	t_h_n->setBuddy(l_h_n);

	tl->addWidget(t_h_n);
	tl->addWidget(l_h_n);
	tl->addWidget(t_h_w);
	tl->addWidget(l_h_w);
	tl->addWidget(t_h_h);
	tl->addWidget(l_h_h);
	tl->addWidget(b_size);
	tl->addWidget(b_crop);

	connect(b_crop, &QPushButton::clicked, hall, &THall::crop);
	connect(b_size, &QPushButton::clicked, this, &THallEdit::setSize);

	c_box = new TComboBox();
	connect(c_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
	        &THallEdit::changeIndex);
	c_box->load(getPath());

//	tl->setAlignment(Qt::AlignTop);
	l->addWidget(c_box);
	l->addLayout(tl);
	// Size - Top menu

	l->addWidget(hall);

	// Save - Bottom menu
	QHBoxLayout *bl = new QHBoxLayout;

	QPushButton *b_save = new QPushButton("Сохранить"), *b_rest = new QPushButton("Сбросить");

	bl->addWidget(b_save);
	bl->addWidget(b_rest);

	connect(b_save, &QPushButton::clicked, this, &THallEdit::save);
	connect(b_rest, &QPushButton::clicked, this, &THallEdit::reset);

	l->addLayout(bl);
	// Save - Bottom menu

	setLayout(l);
}

void THallEdit::save() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/update", getParams()).toString();

		if (o == "successful") {
			reset();
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

void THallEdit::reset() {
	const QJsonObject &o = QJsonDocument::fromJson(obj["json"].toString().toUtf8()).object();
	id = obj["id"].toInt();
	hall->fromJson(o);
	l_h_w->setText(QString::number(o["width"].toInt()));
	l_h_h->setText(QString::number(o["height"].toInt()));
	l_h_n->setText(obj["name"].toString());
}

void THallEdit::setSize() {
	hall->setSize(l_h_w->text().toInt(), l_h_h->text().toInt());
}

QString THallEdit::getPath() {
	return "t_halls";
}

QMap<QString, QString> THallEdit::getParams() {
	return {
			{"id",   QString::number(id)},
			{"name", l_h_n->text()},
			{"json", QJsonDocument(hall->toJson()).toJson(QJsonDocument::Compact)}
	};
}

void THallEdit::changeIndex(int i) {
	if (c_box->getIndex() != "0") {
		obj = TDB().request(getPath() + "/" + c_box->getIndex()).toObject();
		reset();
	}
}
