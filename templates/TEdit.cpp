#include <utils/TDB.h>
#include "TEdit.h"

TEdit::TEdit() {
	QVBoxLayout *l = new QVBoxLayout;
	layout = new QFormLayout;

	c_box = new TComboBox();

	l->addWidget(c_box, 0, Qt::AlignTop);

	// Scroll
	QScrollArea *scroll = new QScrollArea;
	QWidget *w = new QWidget;

	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 5, 0);
	layout->setAlignment(Qt::AlignTop);

	w->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	w->setLayout(layout);

	scroll->setWidget(w);
	scroll->setWidgetResizable(true);
	scroll->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
	scroll->setFrameStyle(QFrame::NoFrame);

	l->addWidget(scroll);
	// Scroll

	b_create = new QPushButton("Сохранить");
	b_reset = new QPushButton("Сбросить");

	connect(c_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &TEdit::changeIndex);
	connect(b_create, &QPushButton::clicked, this, &TEdit::submit);
	connect(b_reset, &QPushButton::clicked, this, &TEdit::reset);

	QHBoxLayout *vl = new QHBoxLayout;
	vl->addWidget(b_create);
	vl->addWidget(b_reset);
	vl->setAlignment(Qt::AlignBottom);

	l->addSpacing(10);
	l->addLayout(vl);
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
