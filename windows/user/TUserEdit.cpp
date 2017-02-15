#include <utils/TDB.h>
#include "TUserEdit.h"

TUserEdit::TUserEdit() {
	l_fio = new QLineEdit();
	l_pos = new QLineEdit();
	l_login = new QLineEdit();
	l_passw = new QLineEdit();
	l_phone = new QLineEdit();
	l_perms = new TCheckBox("u_perms");

	l_passw->setEchoMode(QLineEdit::PasswordEchoOnEdit);


	layout->setMargin(0);

	layout->addRow("ФИО:", l_fio);
	layout->addRow("Должность:", l_pos);
	layout->addRow("Логин:", l_login);
	layout->addRow("Пароль:", l_passw);
	layout->addRow("Телефон:", l_phone);
	layout->addRow("Права доступа", l_perms);

	c_box->load("u_apis");
	load();
}

void TUserEdit::reset() {
	id = obj["id"].toInt();

	l_fio->setText(obj["fio"].toString());
	l_pos->setText(obj["position"].toString());
	l_login->setText(obj["login"].toString());
	l_passw->setText("");
	l_phone->setText(obj["tel_num"].toString());

	l_perms->setIds(obj["perms"].toArray());
}

QString TUserEdit::getPath() {
	return "u_apis";
}

QMap<QString, QString> TUserEdit::getParams() {
	return {
			{"id",       QString::number(id)},
			{"fio",      l_fio->text()},
			{"position", l_pos->text()},
			{"login",    l_login->text()},
			{"password", l_passw->text()},
			{"tel_num",  l_phone->text()},
			{"perms",    l_perms->getIds()}
	};
}
