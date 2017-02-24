#include <utils/TDB.h>
#include "TEdit.h"

TEdit::TEdit() {
	QVBoxLayout *l = new QVBoxLayout;
	layout = new QFormLayout;

	c_box = new TComboBox();

	b_create = new QPushButton("Сохранить");
	b_reset = new QPushButton("Сбросить");

	connect(c_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &TEdit::changeIndex);
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

void TEdit::load() {
	if (c_box->getIndex() != "0") {
		obj = TDB().request(getPath() + "/" + c_box->getIndex()).toObject();
		reset();
	}
}

void TEdit::submit() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/update", getParams()).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}
