#include "TArticleCreate.h"
#include <utils/TDB.h>


TArticleCreate::TArticleCreate() {
	name = new QLineEdit();
	desc_s = new QTextEdit();
	desc = new QTextEdit();


	layout->addRow("Заголовок:", name);
	layout->addRow("Краткое Описание:", desc_s);
	layout->addRow("Описание:", desc);

}

void TArticleCreate::create() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("articles/create", {
				                          {"name",   name->text()},
				                          {"desc_s", desc_s->toPlainText()},
				                          {"desc",   desc->toPlainText()}
		                          }

		).toString();

		if (o == "successful") {
			reset();
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

void TArticleCreate::reset() {
	name->clear();
	desc_s->clear();
	desc->clear();

}
