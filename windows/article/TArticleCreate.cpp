#include "TArticleCreate.h"
#include <utils/TDB.h>


TArticleCreate::TArticleCreate() {
	name = new QLineEdit;
	desc_s = new QTextEdit;
	desc = new QTextEdit;
	img = new TFileUpload;

	layout->addRow("Заголовок:", name);
	layout->addRow("Изображение:", img);
	layout->addRow("Краткое Описание:", desc_s);
	layout->addRow("Описание:", desc);
}

void TArticleCreate::reset() {
	name->clear();
	desc_s->clear();
	desc->clear();
	img->clear();
}

QString TArticleCreate::getPath() {
	return "articles";
}

QMap<QString, QString> TArticleCreate::getParams() {
	return {
			{"name",   name->text()},
			{"desc_s", desc_s->toPlainText()},
			{"desc",   desc->toPlainText()},
			{"img",    img->getUrl()}
	};
}
