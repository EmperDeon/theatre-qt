#include <utils/TDB.h>
#include "TUser.h"

// TUser
TUser::TUser(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();

	l_fio = new QLineEdit(o["fio"].toString());
	l_pos = new QLineEdit(o["position"].toString());

	l_login = new QLineEdit(o["login"].toString());
	l_phone = new QLineEdit(o["phone"].toString());

	b_edt = new QPushButton("Изменить");
	b_del = new QPushButton("Удалить");

	l_fio->setEnabled(false);
	l_pos->setEnabled(false);
	l_login->setEnabled(false);
	l_phone->setEnabled(false);

	b_edt->setMaximumWidth(100);
	b_del->setMaximumWidth(100);

	connect(b_edt, &QPushButton::clicked, this, &TUser::edt);
	connect(b_del, &QPushButton::clicked, this, &TUser::del);

	QFormLayout *fl1 = new QFormLayout;
	fl1->addRow("ФИО:", l_fio);
	fl1->addRow("Должность:", l_pos);

	QFormLayout *fl2 = new QFormLayout;
	fl2->addRow("Логин:", l_login);
	fl2->addRow("Телефон:", l_phone);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->addWidget(b_edt);
	vl->addWidget(b_del);

	l->addLayout(fl1);
	l->addLayout(fl2);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
	setFrameStyle(QFrame::StyledPanel);

}

void TUser::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	l_fio->setEnabled(!sv);
	l_pos->setEnabled(!sv);
	l_login->setEnabled(!sv);
	l_phone->setEnabled(!sv);
}

void TUser::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("users/delete", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}
}

void TUser::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("users/edit",
		                          {
				                          {"id",       QString::number(id)},
				                          {"fio",      l_fio->text()},
				                          {"position", l_pos->text()},
				                          {"login",    l_login->text()},
				                          {"phone",    l_phone->text()}

		                          }).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}
// TUser