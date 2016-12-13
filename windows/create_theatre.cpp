#include "create_theatre.h"

create_theatre::create_theatre() {

	name = new QLineEdit;
	address = new QLineEdit;
	tel_num = new QLineEdit;
	desc = new QTextEdit;

	l_name = new QLabel("Название театра");
	l_address = new QLabel("Адрес");
	l_tel_num = new QLabel("Телефонный номер");
	l_desc = new QLabel("Описание:");

	l_name->setBuddy(name);
	l_address->setBuddy(address);
	l_tel_num->setBuddy(tel_num);
	l_desc->setBuddy(desc);

	entr = new QPushButton("Добавить");
	cancel = new QPushButton("Отмена");

	connect(entr, SIGNAL(clicked(bool)), this, SLOT (create()));

	l = new QVBoxLayout;
	lh = new QHBoxLayout;

	lh->addWidget(entr);
	lh->addWidget(cancel);

	l->addWidget(l_name);
	l->addWidget(name);
	l->addWidget(l_address);
	l->addWidget(address);
	l->addWidget(l_tel_num);
	l->addWidget(tel_num);
	l->addWidget(l_desc);
	l->addWidget(desc);

	l->addLayout(lh);
	setLayout(l);


}

void create_theatre::create() {
	QJsonObject o;
	o["name"] = name->text();
	o["desc"] = desc->toPlainText();
	o["img"] = "";
	o["address"] = address->text();
	o["tel_num"] = tel_num->text();

	qDebug() << o;
}


