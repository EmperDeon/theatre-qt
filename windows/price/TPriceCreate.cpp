#include <utils/TDB.h>
#include "TPriceCreate.h"

TPriceCreate::TPriceCreate() {
	QVBoxLayout *l = new QVBoxLayout;

	price = new THallPrice();
	price->clear();


	// Top menu
	QHBoxLayout *tl = new QHBoxLayout;
	QLabel *t_poster = new QLabel("Спектакль:"), *t_hall = new QLabel("Зал:");
	c_poster = new TComboBox("posters");
	c_hall = new TComboBox("t_halls");

	connect(c_hall, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
	        &TPriceCreate::selectHall);
	selectHall(0);

	tl->addWidget(t_poster, 1);
	tl->addWidget(c_poster, 8);
	tl->addWidget(t_hall, 1, Qt::AlignRight);
	tl->addWidget(c_hall, 8);

	l->addLayout(tl);
	l->addWidget(price);


	// Save - Bottom menu
	QHBoxLayout *bl = new QHBoxLayout;
	QPushButton *b_save = new QPushButton("Сохранить"), *b_rest = new QPushButton("Сбросить");

	bl->addWidget(b_save);
	bl->addWidget(b_rest);

	connect(b_save, &QPushButton::clicked, this, &TPriceCreate::save);
	connect(b_rest, &QPushButton::clicked, this, &TPriceCreate::reset);


	l->addLayout(bl);

	setLayout(l);
}

void TPriceCreate::save() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/create", getParams()).toString();

		if (o == "successful") {
			reset();
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

void TPriceCreate::reset() {
	price->clear();
}

QString TPriceCreate::getPath() {
	return "t_prices";
}

QMap<QString, QString> TPriceCreate::getParams() {
	return {
			{"poster_id", c_poster->getIndex()},
			{"t_hall_id", c_hall->getIndex()},
			{"json",      QJsonDocument(price->toJson()).toJson()}
	};
}

void TPriceCreate::selectHall(int n) {
	if (c_hall->getIndex() != "0") {
		QString obj = TDB().request("t_halls/" + c_hall->getIndex()).toObject()["json"].toString();
		price->loadHall(QJsonDocument::fromJson(obj.toUtf8()).object());
	}
}
