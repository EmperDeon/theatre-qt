#include <utils/TDB.h>
#include "TPoster.h"

TPoster::TPoster(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();

	l_name = new QLineEdit(o["name"].toString());
	l_hall = new QLineEdit(o["hall"].toString());
	l_date = new QDateTimeEdit(QDateTime::fromString(o["date"].toString(), "dd.MM.yyyy hh:mm"));

	l_name->setEnabled(false);
	l_hall->setEnabled(false);
	l_date->setEnabled(false);

	l_date->setDisplayFormat("dd.MM.yyyy hh:mm");

	b_edt = new QPushButton("Изменить");
	b_del = new QPushButton("Удалить");

	b_edt->setMaximumWidth(100);
	b_del->setMaximumWidth(100);

	connect(b_edt, &QPushButton::clicked, this, &TPoster::edt);
	connect(b_del, &QPushButton::clicked, this, &TPoster::del);

	QFormLayout *fl1 = new QFormLayout;
	fl1->addRow("Название:", l_name);
	fl1->addRow("Зал:", l_hall);
	fl1->addRow("Дата:", l_date);


	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);
	vl->addWidget(b_edt);
	vl->addWidget(b_del);

	l->addLayout(fl1);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}

void TPoster::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	l_date->setEnabled(!sv);

}

void TPoster::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("posters/edit",
		                          {
				                          {"id",   QString::number(id)},
				                          {"date", l_date->dateTime().toString("dd.MM.yyyy hh:mm")},

		                          }
		).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}

void TPoster::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("posters/delete", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}
}
