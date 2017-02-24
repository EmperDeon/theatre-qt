#include <utils/TDB.h>
#include "TTheatreEdit.h"

TTheatreEdit::TTheatreEdit() {
	name = new QLineEdit;
	phone = new QLineEdit;
	address = new QLineEdit;
	desc = new QTextEdit;
	img = new TFileUpload;
	halls = new TListBox("t_halls");

	layout->setMargin(0);

	layout->addRow("Название:", name);
	layout->addRow("Телефонный номер:", phone);
	layout->addRow("Адрес:", address);
	layout->addRow("Описание:", desc);
	layout->addRow("Изображение:", img);
	layout->addRow("Залы:", halls);

	c_box->load(getPath());
	if (c_box->count() == 1)
		c_box->setVisible(false);

	load();
}

void TTheatreEdit::reset() {
	id = obj["id"].toInt();

	name->setText(obj["name"].toString());
	phone->setText(obj["tel_num"].toString());
	address->setText(obj["address"].toString());
	desc->setText(obj["desc"].toString());
	img->load(obj["img"].toString());

	halls->load("t_halls");
}

QString TTheatreEdit::getPath() {
	return "theatres";
}

QMap<QString, QString> TTheatreEdit::getParams() {
//	if (!halls->getItems().isEmpty()) { TODO: Think
//		if (QMessageBox::warning(this, "Внимание !",
//		                         "При удалении зала, удаялтся также и все афиши в этом зале. \nПродолжить ?",
//		                         QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
//			return;
//		}
//	}

	return {
			{"id",          QString::number(id)},
			{"name",        name->text()},
			{"tel_num",     phone->text()},
			{"address",     address->text()},
			{"desc",        desc->toPlainText()},
			{"img",         img->getUrl()},

			{"t_halls_del", halls->getItems()},
			{"t_halls_new", halls->getAdded()}
	};
}
