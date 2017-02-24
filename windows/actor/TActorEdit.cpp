#include "TActorEdit.h"

TActorEdit::TActorEdit() {
	name = new QLineEdit;
	desc = new QTextEdit;
	img = new TFileUpload;

	layout->addRow("ФИО:", name);
	layout->addRow("Биография:", desc);
	layout->addRow("Фотография:", img);

	c_box->load(getPath());
	load();
}

void TActorEdit::reset() {
	id = obj["id"].toInt();

	name->setText(obj["name"].toString());
	desc->setText(obj["desc"].toString());
	img->load(obj["img"].toString());
}

QString TActorEdit::getPath() {
	return "actors";
}

QMap<QString, QString> TActorEdit::getParams() {
	return {
			{"name", name->text()},
			{"desc", desc->toPlainText()},
			{"img",  img->getUrl()}
	};
}
