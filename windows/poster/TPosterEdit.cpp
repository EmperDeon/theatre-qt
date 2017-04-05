#include <utils/TDB.h>
#include <windows/price/TPriceDialog.h>
#include "TPosterEdit.h"

TPosterEdit::TPosterEdit() {
	name = new TComboBox("t_performances");
	date = new QDateTimeEdit();
	l_prices = new QLabel("Не заданы");
	QPushButton *b_prices = new QPushButton("Задать цены");

	date->setDisplayFormat("dd-MM-yyyy hh:mm");

	layout->setMargin(0);

	layout->addRow("Дата и время:", date);
	layout->addRow("Цены:", l_prices);
	layout->addRow("", b_prices);

	connect(b_prices, &QPushButton::clicked, this, &TPosterEdit::setHalls);
	layout->setAlignment(Qt::AlignTop);

	c_box->load("posters");
	load();
}

void TPosterEdit::reset() {
	id = obj["id"].toInt();

	name->setCurrentItem(obj["perf"].toObject()["id"].toInt());
	date->setDateTime(QDateTime::fromString(obj["date"].toString(), "dd-MM-yyyy hh:mm"));
}

QString TPosterEdit::getPath() {
	return "posters";
}

QMap<QString, QString> TPosterEdit::getParams() {
	return {
			{"id",        QString::number(id)},
			{"t_perf_id", name->getIndex()},
			{"date",      date->dateTime().toString("dd-MM-yyyy hh:mm")}, // TODO: Fix to current datetime format
			{"price",     price}

	};
}

void TPosterEdit::setHalls() {
	int hall = TDB().request("t_perfs/" + name->getIndex()).toObject()["hall"].toObject()["id"].toInt(0);

	if (hall == 0) {
		QMessageBox::critical(this, "Ошибка", "Не задан зал");
	} else {
		price = TPriceDialog::getPrice(hall);
	}

	if (price == "") {
		l_prices->setText("Не заданы");

	} else {
		l_prices->setText("Заданы");
	}
}
