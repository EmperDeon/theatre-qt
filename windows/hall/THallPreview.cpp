#include <windows/user/TUsers.h>
#include <utils/TDB.h>
#include <windows/TMainWindow.h>
#include "THallPreview.h"
#include "utils/TFileUpload.h"

THallPreview::THallPreview(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;
	QFormLayout *layout = new QFormLayout;

	id = o["id"].toInt();

	QLabel *lb = new QLabel;
	lb->setPixmap(TFileUpload::getImage(o["preview"]));
	layout->addWidget(lb);
	l->addLayout(layout);


	// Form
	QLabel *l_upd_l = new QLabel("Последнее изменение:");
	QLabel *l_upd = new QLabel;

	l_upd->setEnabled(false);
	l_upd->setStyleSheet("font-size: 11px");
	l_upd->setText(o["timestamps"].toObject()["updated_at"].toString());
	// Form


	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);

	if (TUsers::hasPerm(getPath() + "_edit")) {
		QPushButton *b_edt = new QPushButton("Изменить");
		QPushButton *b_del = new QPushButton("Удалить");

		b_edt->setMaximumWidth(100);
		b_del->setMaximumWidth(100);

		connect(b_edt, &QPushButton::clicked, this, &THallPreview::edt);
		connect(b_del, &QPushButton::clicked, this, &THallPreview::del);

		vl->addWidget(b_edt);
		vl->addWidget(b_del);

		// Last edited row
		layout->addRow(new QLabel(""));
		layout->addRow(l_upd_l, l_upd);
	}

	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
	setFrameStyle(QFrame::StyledPanel);
}

QString THallPreview::getPath() {
	return "t_halls";
}

void THallPreview::edt() {
	TMainWindow::getInstance()->changeCurrent("t_halls_update");
}

void THallPreview::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/destroy", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно удалено");
			this->deleteLater();
		}
	}
}
