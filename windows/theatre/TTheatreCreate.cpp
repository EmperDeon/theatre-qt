#include "TTheatreCreate.h"
#include <utils/TDB.h>


TTheatreCreate::TTheatreCreate() {
	name = new QLineEdit();
	phone = new QLineEdit();
	address = new QLineEdit();
	desc = new QTextEdit();

	list = new TListBox;

	layout->addRow("Название:", name);
	layout->addRow("Телефонный номер:", phone);
	layout->addRow("Адрес:", address);
	layout->addRow("Описание:", desc);
	layout->addRow("Залы:", list);
}

void TTheatreCreate::create() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("theatres/create", {
				                          {"name",      name->text()},
				                          {"tel_num",   phone->text()},
				                          {"address",   address->text()},
				                          {"desc",      desc->toPlainText()},

				                          {"halls_new", list->getAdded().join(',')}
		                          }

		).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			reset();
		}
	}
}

void TTheatreCreate::reset() {
	name->clear();
	phone->clear();
	address->clear();
	desc->clear();

}


