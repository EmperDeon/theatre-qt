#include "TActorCreate.h"
#include <utils/TDB.h>


TActorCreate::TActorCreate() {
	name = new QLineEdit;
	desc = new QTextEdit;
	img = new TFileUpload;

	layout->addRow("ФИО:", name);
	layout->addRow("Биография:", desc);
	layout->addRow("Фотография:", img);
}

void TActorCreate::reset() {
	name->clear();
	desc->clear();
	img->clear();
}

QString TActorCreate::getPath() {
	return "actors";
}

QMap<QString, QString> TActorCreate::getParams() {
	return {
			{"name", name->text()},
			{"desc", desc->toPlainText()},
			{"img",  img->getUrl()}
	};
}
