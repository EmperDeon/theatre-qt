#include <utils/TDB.h>
#include "TArticleEdit.h"

TArticleEdit::TArticleEdit() {
	name = new QLineEdit();
	desc = new QTextEdit();
	desc_s = new QTextEdit();
	img = new TFileUpload;

	layout->setMargin(0);

	layout->addRow("Заголовок:", name);
	layout->addRow("Изображение:", img);
	layout->addRow("Краткое описание:", desc_s);
	layout->addRow("Описание:", desc);

	c_box->load(getPath());
	load();
}

void TArticleEdit::reset() {
	id = obj["id"].toInt();

	name->setText(obj["name"].toString());
	desc_s->setText(obj["desc_s"].toString());
	desc->setText(obj["desc"].toString());
	img->load(obj["img"].toString());
}

QString TArticleEdit::getPath() {
	return "articles";
}

QMap<QString, QString> TArticleEdit::getParams() {
	return {
			{"id",     QString::number(id)},
			{"name",   name->text()},
			{"desc_s", desc_s->toPlainText()},
			{"desc",   desc->toPlainText()},
			{"img",    img->getUrl()}
	};
}
