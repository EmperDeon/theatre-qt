#include "TArticle.h"

TArticle::TArticle(QJsonObject o) : TTModel(o) {
	title = new QLineEdit(o["name"].toString());
	desc = new QTextEdit(o["desc_s"].toString());

	title->setEnabled(false);
	desc->setEnabled(false);

	layout->addRow("Заголовок", title);
	layout->addRow("Краткое описание:", desc);
}

void TArticle::setFEnabled(bool b) {
	title->setEnabled(b);
	desc->setEnabled(b);
}

QMap<QString, QString> TArticle::getParams() {
	return {
			{"id",     QString::number(id)},
			{"name",   title->text()},
			{"desc_s", desc->toPlainText()}
	};
}

QString TArticle::getPath() {
	return "articles";
}
