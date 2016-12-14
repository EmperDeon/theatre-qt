#include <QtWidgets/QFormLayout>
#include "theatre.h"

theatre::theatre(QJsonObject o) {
	name = new QLineEdit(o["name"].toString());
	address = new QLineEdit(o["address"].toString());
	tel_num = new QLineEdit(o["tel_num"].toString());
	desc = new QTextEdit(o["desc"].toString());

	name->setEnabled(false);
	address->setEnabled(false);
	tel_num->setEnabled(false);
	desc->setEnabled(false);

	l_name = new QLabel("Название театра");
	l_address = new QLabel("Адрес");
	l_tel_num = new QLabel("Телефонный номер");
	l_desc = new QLabel("Описание:");

//	l_name->setBuddy(name);
//	l_address->setBuddy(address);
//	l_tel_num->setBuddy(tel_num);
//	l_desc->setBuddy(desc);

	edit = new QPushButton("Изменить");
	del = new QPushButton("Удалить");

	l = new QHBoxLayout;
	l1 = new QVBoxLayout;
	l2 = new QVBoxLayout;

	l1->addWidget(edit);
	l1->addWidget(del);
	l1->setAlignment(Qt::AlignTop);

	connect(edit, &QPushButton::clicked, this, &theatre::CEdit);

	QFormLayout *fl = new QFormLayout;

	fl->addRow(l_name, name);
	fl->addRow(l_address, address);
	fl->addRow(l_tel_num, tel_num);
	fl->addRow(l_desc, desc);
	l->addLayout(fl);
	l->addLayout(l1);

	setLayout(l);

}

void theatre::CEdit() {
	if (edit->text() == "Изменить") {
		edit->setText("Сохранить");
		name->setEnabled(true);
		address->setEnabled(true);
		tel_num->setEnabled(true);
		desc->setEnabled(true);

	} else {
		name->setEnabled(false);
		address->setEnabled(false);
		tel_num->setEnabled(false);
		desc->setEnabled(false);

		edit->setText("Изменить");
	}
}


