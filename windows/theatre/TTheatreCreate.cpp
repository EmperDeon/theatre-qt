#include "TTheatreCreate.h"
#include <utils/TDB.h>


TTheatreCreate::TTheatreCreate() {
	name = new QLineEdit();
	phone = new QLineEdit();
	address = new QLineEdit();
	desc = new QTextEdit();
	img = new TFileUpload();

	layout->addRow("Название:", name);
	layout->addRow("Телефонный номер:", phone);
	layout->addRow("Адрес:", address);
	layout->addRow("Описание:", desc);
	layout->addRow("Изображение:", img);
}

void TTheatreCreate::reset() {
	name->clear();
	phone->clear();
	address->clear();
	desc->clear();
	img->clear();
}

QString TTheatreCreate::getPath() {
	return "theatres";
}

QMap<QString, QString> TTheatreCreate::getParams() { // TODO: Fix
	return {
			{"name",    name->text()},
			{"tel_num", phone->text()},
			{"address", address->text()},
			{"desc",    desc->toPlainText()},
			{"img",     img->getUrl()}
	};
}


