#include "THallTools.h"

THallTools::THallTools() {
	QHBoxLayout *l = new QHBoxLayout;
	bg = new QButtonGroup;

	// Tool buttons
	QList<QPushButton *> butt;

	butt << new QPushButton(QIcon(":/h_pen.png"), "");
	butt << new QPushButton(QIcon(":/h_ers.png"), "");
	butt << new QPushButton(QIcon(":/h_set.png"), "");
	butt << new QPushButton(QIcon(":/h_sect.png"), "");

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

	// Tool 3 settings
	seat_w = new QWidget;
	QHBoxLayout *l2 = new QHBoxLayout;

	QLabel *l2_1 = new QLabel("Начинать с:"), *l2_2 = new QLabel("Направление:");
	seat_start = new QLineEdit;
	seat_direc = new QComboBox;

	seat_start->setValidator(new QIntValidator(1, 200));
	l2_1->setBuddy(seat_start);

	seat_direc->addItems({"Справа налево", "Слева направо"});
	l2_2->setBuddy(seat_direc);

	l2->setMargin(0);
	l2->addWidget(l2_1);
	l2->addWidget(seat_start);
	l2->addWidget(l2_2);
	l2->addWidget(seat_direc);

	seat_w->setLayout(l2);
	seat_w->setVisible(false);
	l->addWidget(seat_w);


	// Tool 4 settings
	sect_w = new QWidget;
	QHBoxLayout *l3 = new QHBoxLayout;

	sect_box = new QComboBox;
	QPushButton *l3_c = new QPushButton("Создать новый сектор");

	l3->setMargin(0);
	l3->addWidget(sect_box);
	l3->addWidget(l3_c);

	connect(l3_c, &QPushButton::clicked, [=]() {
		const THallSect &t = THallToolSect::getNewSect();
		if (t.name != "")
			sect_list.insert(sect_list.size(), t);

		updateSect();
	});

	sect_w->setLayout(l3);
	sect_w->setVisible(false);
	l->addWidget(sect_w);

	sect_list.insert(0, THallSect("Партер", "P", QColor(255, 0, 0, 50)));
	sect_list.insert(1, THallSect("Балкон", "B", QColor(0, 0, 255, 50)));

	updateSect();
	// Tool settings

	l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);
	l->setAlignment(Qt::AlignLeft);

	connect(bg, static_cast<void (QButtonGroup::*)(int, bool)>(&QButtonGroup::buttonToggled),
	        [=](int id, bool checked) {
		        if (id == 2) {
			        seat_w->setVisible(checked);
		        } else if (id == 3) {
			        sect_w->setVisible(checked);
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

void THallTools::updateSect() {
	sect_box->clear();

	for (THallSect s : sect_list) {
		sect_box->addItem(s.name);
	}
}

QPair<int, THallSect *> THallTools::getCurrentSect() {
	return QPair<int, THallSect *>(sect_box->currentIndex(), &sect_list[sect_box->currentIndex()]);
}

QMap<int, THallSect> THallTools::getSectors() {
	return sect_list;
}

THallToolSect::THallToolSect() {
	QFormLayout *l = new QFormLayout;
	QHBoxLayout *hl = new QHBoxLayout;
	QButtonGroup *bg = new QButtonGroup;

	l_name = new QLineEdit;
	l_pref = new QLineEdit;

	this->setStyleSheet("QPushButton:checked { background-color: red; }");
	QList<QColor> b_list;

	b_list << QColor(255, 0, 0);
	b_list << QColor(0, 255, 0);
	b_list << QColor(0, 0, 255);
	b_list << QColor(255, 127, 0);
	b_list << QColor(186, 0, 255);

	int i = 0;
	for (QColor c : b_list) {
		QPushButton *bt = new QPushButton;
		c.setAlpha(100);

		bt->setCheckable(true);
		bt->setFixedSize(30, 30);
		bt->setProperty("color", c);
		bt->setStyleSheet("background-color: " + c.name(QColor::HexArgb) + ";");
		bg->addButton(bt, i++);

		connect(bg, static_cast<void (QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
		        [=](QAbstractButton *id, bool checked) {
			        l_color = id->property("color").value<QColor>();
		        });

		hl->addWidget(bt);
	}

	bg->button(0)->setChecked(true);

	l->addRow("Название: ", l_name);
	l->addRow("Префикс: ", l_pref);
	l->addRow("Цвет: ", hl);


	QPushButton *b_acc = new QPushButton("Добавить"), *b_rej = new QPushButton("Отмена");

	connect(b_acc, &QPushButton::clicked, this, &THallToolSect::accept);
	connect(b_rej, &QPushButton::clicked, this, &THallToolSect::reject);

	l->addRow(b_acc, b_rej);


	setLayout(l);
}

THallSect THallToolSect::getNewSect() {
	auto t = new THallToolSect;
	int r = t->exec();

	if (r)
		return THallSect(t->l_name->text(), t->l_pref->text(), t->l_color);
	else
		return THallSect();
}
