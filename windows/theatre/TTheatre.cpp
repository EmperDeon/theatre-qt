#include "TTheatre.h"

TTheatre::TTheatre(QJsonObject o) : TTModel(o) {
	name = new QLineEdit(o["name"].toString());
	phone = new QLineEdit(o["tel_num"].toString());
	address = new QLineEdit(o["address"].toString());
	desc = new QTextEdit(o["desc"].toString());

	name->setEnabled(false);
	phone->setEnabled(false);
	address->setEnabled(false);
	desc->setEnabled(false);

	phone->setValidator(new QRegExpValidator(QRegExp("[\\d,\\(,\\),\\-]+")));

	layout->addRow("Название:", name);
	layout->addRow("Телефонный номер:", phone);
	layout->addRow("Адрес:", address);
	layout->addRow("Описание:", desc);
}

QString TTheatre::getPath() {
	return "theatres";
}

void TTheatre::setFEnabled(bool b) {
	name->setEnabled(b);
	phone->setEnabled(b);
	address->setEnabled(b);
	desc->setEnabled(b);
}

QMap<QString, QString> TTheatre::getParams() {
	return {
			{"id",      QString::number(id)},
			{"name",    name->text()},
			{"tel_num", phone->text()},
			{"address", address->text()},
			{"desc",    desc->toPlainText()}
	};
}
