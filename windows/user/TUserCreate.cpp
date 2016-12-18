#include <utils/TDB.h>
#include "TUserCreate.h"

TUserCreate::TUserCreate() {
	QVBoxLayout *l = new QVBoxLayout;

	l_fio = new QLineEdit();
	l_pos = new QLineEdit();

	l_login = new QLineEdit();
	l_passw = new QLineEdit();
	l_phone = new QLineEdit();

	l_perms = new TListBox("u__perms");

	b_create = new QPushButton("Создать");
	b_reset = new QPushButton("Сбросить");

	l_passw->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	connect(b_create, &QPushButton::clicked, this, &TUserCreate::create);
	connect(b_reset, &QPushButton::clicked, this, &TUserCreate::reset);

	QFormLayout *fl = new QFormLayout;
	fl->addRow("ФИО:", l_fio);
	fl->addRow("Должность:", l_pos);
	fl->addRow("Логин:", l_login);
	fl->addRow("Пароль:", l_passw);
	fl->addRow("Телефон:", l_phone);
	fl->addRow("Права доступа:", l_perms);

	QHBoxLayout *vl = new QHBoxLayout;
	vl->addWidget(b_create);
	vl->addWidget(b_reset);

	l->addLayout(fl);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}

void TUserCreate::create() {
	qDebug() << l_perms->getIds() << l_perms->getIds().join(',');

	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("users/create",
		                          {
				                          {"fio",      l_fio->text()},
				                          {"position", l_pos->text()},
				                          {"login",    l_login->text()},
				                          {"password", l_passw->text()},
				                          {"phone",    l_phone->text()},
				                          {"perms",    l_perms->getIds().join(',')}
		                          }
		).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
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
