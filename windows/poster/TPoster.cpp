#include <utils/TDB.h>
#include "TPoster.h"

TPoster::TPoster(QJsonObject o) : TTModel(o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();

	l_name = new QLineEdit(o["name"].toString());
	l_hall = new QLineEdit(o["hall"].toString());
	l_date = new QDateTimeEdit(QDateTime::fromString(o["date"].toString(), "dd.MM.yyyy hh:mm"));

	l_name->setEnabled(false);
	l_hall->setEnabled(false);
	l_date->setEnabled(false);

	l_date->setDisplayFormat("dd.MM.yyyy hh:mm");


	layout->addRow("Название:", l_name);
	layout->addRow("Зал:", l_hall);
	layout->addRow("Дата:", l_date);
}

QString TPoster::getPath() {
	return "posters";
}

void TPoster::setFEnabled(bool b) {
	l_date->setEnabled(b);
}

QMap<QString, QString> TPoster::getParams() {
	return {
			{"id",   QString::number(id)},
			{"date", l_date->dateTime().toString("dd.MM.yyyy hh:mm")}
	};
}
