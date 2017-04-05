#include <utils/TDB.h>
#include "TPriceDialog.h"

TPriceDialog::TPriceDialog(int hall_id, QJsonObject o) {
	QVBoxLayout *l = new QVBoxLayout;

	price = new THallPrice();
	price->fromJson(o);

	QString obj = TDB().request("t_halls/" + QString::number(hall_id)).toObject()["json"].toString();
	price->loadHall(QJsonDocument::fromJson(obj.toUtf8()).object());

	l->addWidget(price);


	// Save - Bottom menu
	QHBoxLayout *bl = new QHBoxLayout;
	QPushButton *b_save = new QPushButton("Сохранить"), *b_rest = new QPushButton("Сбросить");

	bl->addWidget(b_save);
	bl->addWidget(b_rest);

	connect(b_save, &QPushButton::clicked, this, &TPriceDialog::accept);
	connect(b_rest, &QPushButton::clicked, this, &TPriceDialog::reject);

	l->addLayout(bl);

	setLayout(l);
}

QString TPriceDialog::getPrice(int hall_id, QJsonObject o) {
	TPriceDialog *r = new TPriceDialog(hall_id, o);

	if (r->exec()) {
		return QJsonDocument(r->price->toJson()).toJson(QJsonDocument::Compact);
	} else {
		return "";
	}
}
