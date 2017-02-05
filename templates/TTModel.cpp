#include <utils/TDB.h>
#include "TTModel.h"

TTModel::TTModel(QJsonObject o) {
	l = new QHBoxLayout;

	id = o["id"].toInt();

	b_edt = new QPushButton("Изменить");
	b_del = new QPushButton("Удалить");

	b_edt->setMaximumWidth(100);
	b_del->setMaximumWidth(100);


	connect(b_edt, &QPushButton::clicked, this, &TTModel::edt);
	connect(b_del, &QPushButton::clicked, this, &TTModel::del);


	layout = new QFormLayout;
	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);
	vl->addWidget(b_edt);
	vl->addWidget(b_del);

	l->addLayout(layout);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
	setFrameStyle(QFrame::StyledPanel);
}

void TTModel::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	setFEnabled(!sv);
}

void TTModel::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/destroy", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
//			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}

}

void TTModel::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/update", getParams()).toString();

		if (o == "successful") {
//			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

