#include <utils/TDB.h>
#include "TTheatreEdit.h"

TTheatreEdit::TTheatreEdit() {
	name = new QLineEdit();
	phone = new QLineEdit();
	address = new QLineEdit();
	desc = new QTextEdit();
	list = new TListBox("t_halls");

	layout->setMargin(0);

	layout->addRow("Название:", name);
	layout->addRow("Телефонный номер:", phone);
	layout->addRow("Адрес:", address);
	layout->addRow("Описание:", desc);
	layout->addRow("Залы:", list);

	c_box->setVisible(false);
	load();
}

void TTheatreEdit::submit() {
	if (!list->getItems().isEmpty()) {
		if (QMessageBox::warning(this, "Внимание !",
		                         "При удалении зала, удаялтся также и все афиши в этом зале. \nПродолжить ?",
		                         QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
			return;
		}
	}

	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {


		QString o = TDB().request("theatres/edit", {
				{"id",        QString::number(id)},
				{"name",      name->text()},
				{"tel_num",   phone->text()},
				{"address",   address->text()},
				{"desc",      desc->toPlainText()},

				{"halls_del", list->getItems().join(',')},
				{"halls_new", list->getAdded().join(',')}
		}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

void TTheatreEdit::reset() {
	id = obj["id"].toInt();

	name->setText(obj["name"].toString());
	phone->setText(obj["tel_num"].toString());
	address->setText(obj["address"].toString());
	desc->setText(obj["desc"].toString());
}

void TTheatreEdit::load() {
	obj = TDB().request("theatres/" + c_box->getIndex()).toObject();
	reset();
}
