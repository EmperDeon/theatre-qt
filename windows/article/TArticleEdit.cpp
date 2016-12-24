#include <utils/TDB.h>
#include "TArticleEdit.h"

TArticleEdit::TArticleEdit() {
	name = new QLineEdit();
	desc = new QTextEdit();
	desc_s = new QTextEdit();

	layout->setMargin(0);

	layout->addRow("Заголовок:", name);
	layout->addRow("Краткое описание:", desc_s);
	layout->addRow("Описание:", desc);

	c_box->load("articles");
	load();
}

void TArticleEdit::submit() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("articles/edit", {
				{"id",     QString::number(id)},
				{"name",   name->text()},
				{"desc_s", desc_s->toPlainText()},
				{"desc",   desc->toPlainText()}
		}).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}

void TArticleEdit::reset() {
	id = obj["id"].toInt();

	name->setText(obj["name"].toString());
	desc_s->setText(obj["desc_s"].toString());
	desc->setText(obj["desc"].toString());
}

void TArticleEdit::load() {
	obj = TDB().request("articles/" + c_box->getIndex()).toObject();
	reset();
}
