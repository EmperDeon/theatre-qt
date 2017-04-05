#include <utils/TDB.h>
#include "TCreate.h"

TCreate::TCreate() {
	QVBoxLayout *l = new QVBoxLayout;
	layout = new QFormLayout;

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

	b_create = new QPushButton("Создать");
	b_reset = new QPushButton("Сбросить");

	connect(b_create, &QPushButton::clicked, this, &TCreate::create);
	connect(b_reset, &QPushButton::clicked, this, &TCreate::reset);

	QHBoxLayout *vl = new QHBoxLayout;
	vl->addWidget(b_create);
	vl->addWidget(b_reset);

	l->addSpacing(10);
	l->addLayout(vl);

	setLayout(l);
}

void TCreate::create() {
	if (QMessageBox::question(this, "Создание записи в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/create", getParams()).toString();

		if (o == "successful") {
			reset();
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}

}
