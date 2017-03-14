#include "THallTools.h"

THallTools::THallTools() {
	QHBoxLayout *l = new QHBoxLayout;
	bg = new QButtonGroup;

	QList<QPushButton *> butt;

	butt << new QPushButton(QIcon(":/h_pen.png"), "");
	butt << new QPushButton(QIcon(":/h_ers.png"), "");
	butt << new QPushButton(QIcon(":/h_set.png"), "");

	bg->setExclusive(true);

	l->addWidget(new QLabel("Текущий режим: "));

	int i = 0;
	for (auto b : butt) {
		b->setCheckable(true);
		b->setFixedSize(40, 40);
		b->setIconSize(QSize(30, 30));

		bg->addButton(b, i++);
		l->addWidget(b);
	}

	butt[0]->setChecked(true);

	l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);
	l->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	setFixedHeight(45);
	setLayout(l);
}

int THallTools::getCurrentId() {
	return bg->checkedId();
}

void THallTools::setCurrentId(int i) {
	bg->button(i)->setChecked(true);
}

