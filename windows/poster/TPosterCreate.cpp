#include "TPosterCreate.h"
#include <utils/TDB.h>


TPosterCreate::TPosterCreate() {
	name = new TComboBox("t__performances");
	hall = new TComboBox("t__halls");
	date = new QDateTimeEdit();

	date->setDisplayFormat("dd.MM.yyyy hh:mm");
	date->setDate(QDate::currentDate());
	date->setTime(QTime(0, 0));

	layout->addRow("Спектакль:", name);
	layout->addRow("Зал:", hall);
	layout->addRow("Дата и время:", date);

}

void TPosterCreate::create() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("posters/create", {
				                          {"t_perf_id", name->getIndex()},
				                          {"hall_id",   hall->getIndex()},
				                          {"date",      date->dateTime().toString("dd.MM.yyyy hh:mm")}
		                          }

		).toString();

		if (o == "successful") {
			reset();
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

void TPosterCreate::reset() {
	name->setCurrentText(0);
	hall->setCurrentText(0);
	date->setDate(QDate::currentDate());
	date->setTime(QTime(0, 0));
}
