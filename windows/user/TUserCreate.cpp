#include <utils/TDB.h>
#include "TUserCreate.h"

TUserCreate::TUserCreate() {
	l_fio = new QLineEdit();
	l_pos = new QLineEdit();

	l_login = new QLineEdit();
	l_passw = new QLineEdit();
	l_phone = new QLineEdit();

	l_perms = new TCheckBox("u__perms");
	l_passw->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	layout->addRow("ФИО:", l_fio);
	layout->addRow("Должность:", l_pos);
	layout->addRow("Логин:", l_login);
	layout->addRow("Пароль:", l_passw);
	layout->addRow("Телефон:", l_phone);
	layout->addRow("Права доступа:", l_perms);
}

void TUserCreate::create() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("users/create", {
				                          {"fio",      l_fio->text()},
				                          {"position", l_pos->text()},
				                          {"login",    l_login->text()},
				                          {"password", l_passw->text()},
				                          {"phone",    l_phone->text()},
				                          {"perms",    l_perms->getIds().join(',')}
		                          }
		).toString();

		if (o == "successful") {
			reset();
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

void TUserCreate::reset() {
	l_fio->clear();
	l_pos->clear();
	l_login->clear();
	l_passw->clear();
	l_perms->clear();
	l_phone->clear();
}
