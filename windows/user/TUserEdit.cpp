#include <utils/TDB.h>
#include "TUserEdit.h"

TUserEdit::TUserEdit() {
	QVBoxLayout *l = new QVBoxLayout;
	QFormLayout *l_box = new QFormLayout;

	c_box = new TComboBox("users");

	// Sub layout
	l_fio = new QLineEdit();
	l_pos = new QLineEdit();
	l_login = new QLineEdit();
	l_passw = new QLineEdit();
	l_phone = new QLineEdit();
	l_perms = new TListBox("u__perms");

	l_passw->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	l_box->setMargin(0);

	l_box->addRow("ФИО:", l_fio);
	l_box->addRow("Должность:", l_pos);
	l_box->addRow("Логин:", l_login);
	l_box->addRow("Пароль:", l_passw);
	l_box->addRow("Телефон:", l_phone);
	l_box->addRow("Права доступа", l_perms);
	// Sub layout

	b_create = new QPushButton("Сохранить");
	b_reset = new QPushButton("Сбросить");

	connect(c_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeIndex(int)));
	connect(b_create, &QPushButton::clicked, this, &TUserEdit::submit);
	connect(b_reset, &QPushButton::clicked, this, &TUserEdit::reset);

	QHBoxLayout *vl = new QHBoxLayout;
	vl->addWidget(b_create);
	vl->addWidget(b_reset);
	vl->setAlignment(Qt::AlignBottom);

	l->addWidget(c_box, 0, Qt::AlignTop);
	l->addLayout(l_box);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);

	changeIndex(0);
}

void TUserEdit::submit() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("users/edit",
		                          {
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

void TUserEdit::changeIndex(int i) {
	Q_UNUSED(i);

	obj = TDB().request("users/" + c_box->getIndex()).toObject();
	reset();
}
