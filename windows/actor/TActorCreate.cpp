#include "TActorCreate.h"

TActorCreate::TActorCreate() {
	name = new QLineEdit;
	bio = new QTextEdit;

	l_name = new QLabel("ФИО");
	l_bio = new QLabel("Биография");

	l_name->setBuddy(name);
	l_bio->setBuddy(bio);

	entr = new QPushButton("Добавить");
	cancel = new QPushButton("Отмена");

	l_name->setBuddy(name);
	l_bio->setBuddy(bio);

	l = new QVBoxLayout;
	lh = new QHBoxLayout;

	lh->addWidget(entr);
	lh->addWidget(cancel);

	l->addWidget(l_name);
	l->addWidget(name);
	l->addWidget(l_bio);
	l->addWidget(bio);
	l->addLayout(lh);
	setLayout(l);


}
