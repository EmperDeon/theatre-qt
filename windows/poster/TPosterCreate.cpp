#include "TPosterCreate.h"
#include <utils/TDB.h>
#include <windows/price/TPriceDialog.h>


TPosterCreate::TPosterCreate() {
	name = new TComboBox("t_performances");
	date = new QDateTimeEdit();
	l_prices = new QLabel("Не заданы");
	QPushButton *b_prices = new QPushButton("Задать цены");

	date->setDisplayFormat("dd-MM-yyyy hh:mm");
	date->setDate(QDate::currentDate());
	date->setTime(QTime(0, 0));

	layout->addRow("Спектакль:", name);
	layout->addRow("Дата и время:", date);
	layout->addRow("Цены:", l_prices);
	layout->addRow("", b_prices);

	connect(b_prices, &QPushButton::clicked, this, &TPosterCreate::setHalls);
}

void TPosterCreate::reset() {
	name->setCurrentText(0);
	date->setDate(QDate::currentDate());
	date->setTime(QTime(0, 0));
}

QString TPosterCreate::getPath() {
	return "posters";
}

QMap<QString, QString> TPosterCreate::getParams() {
	return {
			{"t_perf_id", name->getIndex()},
			{"date",      date->dateTime().toString("dd-MM-yyyy hh:mm")}, // TODO: Fix to current datetime format
			{"price",     price}
	};
}

void TPosterCreate::setHalls() {
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
