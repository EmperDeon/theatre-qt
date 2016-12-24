#include "TEdit.h"

TEdit::TEdit() {
	QVBoxLayout *l = new QVBoxLayout;
	layout = new QFormLayout;

	c_box = new TComboBox();

	b_create = new QPushButton("Сохранить");
	b_reset = new QPushButton("Сбросить");

	connect(c_box, SIGNAL(currentIndexChanged(int)), this, SLOT(changeIndex(int)));
	connect(b_create, &QPushButton::clicked, this, &TEdit::submit);
	connect(b_reset, &QPushButton::clicked, this, &TEdit::reset);

	QHBoxLayout *vl = new QHBoxLayout;
	vl->addWidget(b_create);
	vl->addWidget(b_reset);
	vl->setAlignment(Qt::AlignBottom);

	l->addWidget(c_box, 0, Qt::AlignTop);
	l->addLayout(layout);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}

void TEdit::changeIndex(int i) {
	Q_UNUSED(i);
	load();
}
