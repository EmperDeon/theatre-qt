#include <utils/TDB.h>
#include "TPosterEdit.h"

TPosterEdit::TPosterEdit() {
	name = new TComboBox("t_performances");
	hall = new TComboBox("t_halls");
	date = new QDateTimeEdit();

	date->setDisplayFormat("dd.MM.yyyy hh:mm");

	layout->setMargin(0);

	layout->addRow("Спектакль:", name);
	layout->addRow("Зал:", hall);
	layout->addRow("Дата и время:", date);
	layout->setAlignment(Qt::AlignTop);

	c_box->load("posters");
	load();
}

void TPosterEdit::reset() {
	id = obj["id"].toInt();

	name->setCurrentItem(obj["perf"].toObject()["id"].toInt());
	hall->setCurrentItem(obj["hall"].toObject()["id"].toInt());
	date->setDateTime(QDateTime::fromString(obj["date"].toString(), "dd.MM.yyyy hh:mm"));
}

QString TPosterEdit::getPath() {
	return "posters";
}

QMap<QString, QString> TPosterEdit::getParams() {
	return {
			{"id",        QString::number(id)},
			{"t_perf_id", name->getIndex()},
			{"hall_id",   hall->getIndex()},
			{"date",      date->dateTime().toString("dd.MM.yyyy hh:mm")}

	};
}
