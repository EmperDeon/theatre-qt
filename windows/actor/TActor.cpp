#include "TActor.h"


TActor::TActor(QJsonObject o) : TTModel(o) {
	name = new QLineEdit(o["name"].toString());
	desc = new QTextEdit(o["desc"].toString());

	name->setEnabled(false);
	desc->setEnabled(false);

	layout->addRow("ФИО:", name);
	layout->addRow("Биография:", desc);
}

void TActor::setFEnabled(bool b) {
	name->setEnabled(b);
	desc->setEnabled(b);
}

QMap<QString, QString> TActor::getParams() {
	return {
			{"id",   QString::number(id)},
			{"name", name->text()},
			{"desc", desc->toPlainText()}
	};
}

QString TActor::getPath() {
	return "actors";
}



