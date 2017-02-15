#include "TPosterCreate.h"
#include <utils/TDB.h>


TPosterCreate::TPosterCreate() {
	name = new TComboBox("t_performances");
	date = new QDateTimeEdit();

	date->setDisplayFormat("dd-MM-yyyy hh:mm");
	date->setDate(QDate::currentDate());
	date->setTime(QTime(0, 0));

	layout->addRow("Спектакль:", name);
	layout->addRow("Дата и время:", date);

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
			{"date",      date->dateTime().toString("dd-MM-yyyy hh:mm")} // TODO: Fix to current datetime format
	};
}
