#include "THallCreate.h"

THallCreate::THallCreate() {
	QVBoxLayout *l = new QVBoxLayout;
	hall = new THall();

	// Size - Top menu
	QHBoxLayout *tl = new QHBoxLayout;

	QPushButton *b_crop = new QPushButton("Обрезать"), *b_size = new QPushButton("Изменить размер");
	l_h_w = new QLineEdit;
	l_h_h = new QLineEdit;
	QLabel *t_h_w = new QLabel("Ширина:"), *t_h_h = new QLabel("Высота:");

	l_h_w->setValidator(new QIntValidator(1, 200));
	l_h_h->setValidator(new QIntValidator(1, 200));
	t_h_w->setBuddy(l_h_w);
	t_h_h->setBuddy(l_h_h);

	tl->addWidget(t_h_w);
	tl->addWidget(l_h_w);
	tl->addWidget(t_h_h);
	tl->addWidget(l_h_h);
	tl->addWidget(b_size);
	tl->addWidget(b_crop);

	connect(b_crop, &QPushButton::clicked, hall, &THall::crop);
	connect(b_size, &QPushButton::clicked, this, &THallCreate::setSize);

//	tl->setAlignment(Qt::AlignTop);
	l->addLayout(tl);
	// Size - Top menu

	l->addWidget(hall);

	// Save - Bottom menu
	QHBoxLayout *bl = new QHBoxLayout;

	QPushButton *b_save = new QPushButton("Сохранить"), *b_rest = new QPushButton("Сбросить");

	bl->addWidget(b_save);
	bl->addWidget(b_rest);

	connect(b_save, &QPushButton::clicked, this, &THallCreate::save);
	connect(b_rest, &QPushButton::clicked, this, &THallCreate::reset);

//	bl->setAlignment(Qt::AlignBottom);
	l->addLayout(bl);
	// Save - Bottom menu

	setLayout(l);
}

void THallCreate::save() {

}

void THallCreate::reset() {

}

void THallCreate::setSize() {
	hall->setSize(l_h_w->text().toInt(), l_h_h->text().toInt());
}
