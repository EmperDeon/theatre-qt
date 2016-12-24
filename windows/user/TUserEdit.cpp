#include <utils/TDB.h>
#include "TUserEdit.h"

TUserEdit::TUserEdit() {
	l_fio = new QLineEdit();
	l_pos = new QLineEdit();
	l_login = new QLineEdit();
	l_passw = new QLineEdit();
	l_phone = new QLineEdit();
	l_perms = new TCheckBox("u__perms");

	l_passw->setEchoMode(QLineEdit::PasswordEchoOnEdit);


	layout->setMargin(0);

	layout->addRow("ФИО:", l_fio);
	layout->addRow("Должность:", l_pos);
	layout->addRow("Логин:", l_login);
	layout->addRow("Пароль:", l_passw);
	layout->addRow("Телефон:", l_phone);
	layout->addRow("Права доступа", l_perms);

	c_box->load("users");
	load();
}

void TUserEdit::submit() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("users/edit", {
				{"id",       QString::number(id)},
				{"fio",      l_fio->text()},
				{"position", l_pos->text()},
				{"login",    l_login->text()},
				{"password", l_passw->text()},
				{"phone",    l_phone->text()},
				{"perms",    l_perms->getIds().join(',')}
		}).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}

void TUserEdit::reset() {
	id = obj["id"].toInt();

	l_fio->setText(obj["fio"].toString());
	l_pos->setText(obj["position"].toString());
	l_login->setText(obj["login"].toString());
	l_passw->setText("");
	l_phone->setText(obj["phone"].toString());

	l_perms->setIds(obj["perms"].toString().split(','));
}

void TUserEdit::load() {
	obj = TDB().request("users/" + c_box->getIndex()).toObject();
	reset();
}
