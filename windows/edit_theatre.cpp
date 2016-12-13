#include "edit_theatre.h"

edit_theatre::edit_theatre() {

	name = new QComboBox;
	e_name = new QLineEdit;
	address = new QLineEdit;
	tel_num = new QLineEdit;
	desc = new QTextEdit;

	l_name = new QLabel("Театр");
	l_e_name = new QLabel("Новое имя");
	l_address = new QLabel("Адрес");
	l_tel_num = new QLabel("Телефонный номер");
	l_desc = new QLabel("Описание:");

	l_name->setBuddy(name);
	l_e_name->setBuddy(l_e_name);
	l_address->setBuddy(address);
	l_tel_num->setBuddy(tel_num);
	l_desc->setBuddy(desc);

	entr = new QPushButton("Изменить");
	cancel = new QPushButton("Отмена");

	l = new QVBoxLayout;
	lh = new QHBoxLayout;


	lh->addWidget(entr);
	lh->addWidget(cancel);

	l->addWidget(l_name);
	l->addWidget(name);
	l->addWidget(l_e_name);
	l->addWidget(e_name);
	l->addWidget(l_address);
	l->addWidget(address);
	l->addWidget(l_tel_num);
	l->addWidget(tel_num);
	l->addWidget(l_desc);
	l->addWidget(desc);

	l->addLayout(lh);
	setLayout(l);


}
