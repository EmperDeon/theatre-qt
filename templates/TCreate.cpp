#include "TCreate.h"

TCreate::TCreate() {
	QVBoxLayout *l = new QVBoxLayout;
	layout = new QFormLayout;

	b_create = new QPushButton("Создать");
	b_reset = new QPushButton("Сбросить");

	connect(b_create, &QPushButton::clicked, this, &TCreate::create);
	connect(b_reset, &QPushButton::clicked, this, &TCreate::reset);

	QHBoxLayout *vl = new QHBoxLayout;
	vl->addWidget(b_create);
	vl->addWidget(b_reset);

	l->addLayout(layout);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}
