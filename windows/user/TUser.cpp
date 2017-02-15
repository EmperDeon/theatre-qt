#include <utils/TDB.h>
#include "TUser.h"

// TUser
TUser::TUser(QJsonObject o) : TTModel(o) {
	l_fio = new QLineEdit(o["fio"].toString());
	l_pos = new QLineEdit(o["position"].toString());

	l_login = new QLineEdit(o["login"].toString());
	l_phone = new QLineEdit(o["tel_num"].toString());

	l_fio->setEnabled(false);
	l_pos->setEnabled(false);
	l_login->setEnabled(false);
	l_phone->setEnabled(false);

	QFormLayout *fl1 = new QFormLayout;
	fl1->addRow("ФИО:", l_fio);
	fl1->addRow("Должность:", l_pos);

	QFormLayout *fl2 = new QFormLayout;
	fl2->addRow("Логин:", l_login);
	fl2->addRow("Телефон:", l_phone);

	l->insertLayout(0, fl1);
	l->insertLayout(1, fl2);
}

QString TUser::getPath() {
	return "u_apis";
}

void TUser::setFEnabled(bool b) {
	l_fio->setEnabled(b);
	l_pos->setEnabled(b);
	l_login->setEnabled(b);
	l_phone->setEnabled(b);
}

QMap<QString, QString> TUser::getParams() {
	return {
			{"id",       QString::number(id)},
			{"fio",      l_fio->text()},
			{"position", l_pos->text()},
			{"login",    l_login->text()},
			{"tel_num",  l_phone->text()}

	};
}
// TUser