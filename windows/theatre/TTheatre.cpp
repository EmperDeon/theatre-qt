#include "TTheatre.h"

TTheatre::TTheatre(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();

	name = new QLineEdit(o["name"].toString());
	phone = new QLineEdit(o["tel_num"].toString());
	address = new QLineEdit(o["address"].toString());
	desc = new QTextEdit(o["desc"].toString());


	b_edt = new QPushButton("Изменить");
	b_del = new QPushButton("Удалить");

	name->setEnabled(false);
	phone->setEnabled(false);
	address->setEnabled(false);
	desc->setEnabled(false);

	b_edt->setMaximumWidth(100);
	b_del->setMaximumWidth(100);

	connect(b_edt, &QPushButton::clicked, this, &TTheatre::edt);
	connect(b_del, &QPushButton::clicked, this, &TTheatre::del);

	QFormLayout *fl1 = new QFormLayout;
	fl1->addRow("Название:", name);
	fl1->addRow("Телефонный номер:", phone);
	fl1->addRow("Адрес:", address);
	fl1->addRow("Описание:", desc);


	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);
	vl->addWidget(b_edt);
	vl->addWidget(b_del);

	l->addLayout(fl1);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}

void TTheatre::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	name->setEnabled(!sv);
	phone->setEnabled(!sv);
	address->setEnabled(!sv);
	desc->setEnabled(!sv);
}

void TTheatre::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("theatres/delete", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}
}

void TTheatre::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("theatres/edit",
		                          {
				                          {"id",      QString::number(id)},
				                          {"name",    name->text()},
				                          {"tel_num", phone->text()},
				                          {"address", address->text()},
				                          {"desc",    desc->toPlainText()}


		                          }).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}
