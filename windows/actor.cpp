#include "actor.h"

actor::actor(QJsonObject o) {
	name = new QLineEdit(o["name"].toString());
	bio = new QTextEdit(o["bio"].toString());

	l_name = new QLabel("Фио");
	l_bio = new QLabel("Описание:");

	l_name->setBuddy(name);
	l_bio->setBuddy(bio);

	edit = new QPushButton("Изменить");
	del = new QPushButton("Удалить");

	l = new QHBoxLayout;
	l1 = new QVBoxLayout;
	l2 = new QVBoxLayout;

	l1->addWidget(edit);
	l1->addWidget(del);
	l1->setAlignment(Qt::AlignTop);

	l2->addWidget(l_name);
	l2->addWidget(name);
	l2->addWidget(l_bio);
	l2->addWidget(bio);
	l->addLayout(l2);
	l->addLayout(l1);


	setLayout(l);


}
