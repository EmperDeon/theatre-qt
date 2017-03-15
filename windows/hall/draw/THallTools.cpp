#include "THallTools.h"

THallTools::THallTools() {
	QHBoxLayout *l = new QHBoxLayout;
	bg = new QButtonGroup;

	// Tool buttons
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
	// Tool buttons

	// Tool settings
	seat_w = new QWidget;
	QHBoxLayout *l3 = new QHBoxLayout;

	QLabel *l3_1 = new QLabel("Начинать с:"), *l3_2 = new QLabel("Направление:");
	seat_start = new QLineEdit;
	seat_direc = new QComboBox;

	seat_start->setValidator(new QIntValidator(1, 200));
	l3_1->setBuddy(seat_start);

	seat_direc->addItems({"Справа налево", "Слева направо"});
	l3_2->setBuddy(seat_direc);

	l3->setMargin(0);
	l3->addWidget(l3_1);
	l3->addWidget(seat_start);
	l3->addWidget(l3_2);
	l3->addWidget(seat_direc);

	seat_w->setLayout(l3);
	seat_w->setVisible(false);
	l->addWidget(seat_w);
	// Tool settings

	l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);
	l->setAlignment(Qt::AlignLeft);

	connect(bg, static_cast<void (QButtonGroup::*)(int, bool)>(&QButtonGroup::buttonToggled),
	        [=](int id, bool checked) {
		        if (id == 2) {
			        seat_w->setVisible(checked);
		        }
	        });

	setFixedHeight(45);
	setLayout(l);
}

int THallTools::getCurrentId() {
	return bg->checkedId();
}

void THallTools::setCurrentId(int i) {
	bg->button(i)->setChecked(true);
}

THallSeatSett THallTools::getSeatSettings() {
	return THallSeatSett(seat_start->text().toInt(), seat_direc->currentIndex() == 0);
}

