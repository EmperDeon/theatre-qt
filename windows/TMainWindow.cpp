#include <QtWidgets/QHBoxLayout>
#include "windows/create_theatre.h"
#include "windows/edit_theatre.h"
#include "windows/theatres.h"
#include "windows/create_actor.h"
#include "windows/actors.h"
#include "TMainWindow.h"
#include "TUser.h"
#include <QDebug>

TMainWindow::TMainWindow() {
	QWidget *nw = new QWidget;
	l = new QHBoxLayout;
	w_menu = new TMainMenu(this);

	l->setContentsMargins(0, 0, 0, 0);

	l->addWidget(w_menu);

	nw->setLayout(l);
	this->setCentralWidget(nw);

	changeCurrent("main");
}

void TMainWindow::changeCurrent(QString s) {
	if (w_curr != nullptr)
		w_curr->deleteLater(), w_curr = nullptr;

	if (s == "main") {
		w_curr = getNewMainWidget();

	} else if (s == "show create_theatre") {
		w_curr = new create_theatre;

	} else if (s == "show edit_theatre") {
		w_curr = new edit_theatre;

	} else if (s == "show theatres") {
		w_curr = new theatres;

	} else if (s == "show create_actors") {
		w_curr = new create_actor;

	} else if (s == "show actors") {
		w_curr = new actors;

	} else if (s == "show users") {
		w_curr = new TUsers;
	}

	s_curr = s;
	if (w_curr != nullptr)
		l->addWidget(w_curr);
}

QWidget *TMainWindow::getNewMainWidget() {
	QWidget *r = new QWidget;
	QVBoxLayout *l = new QVBoxLayout;

	QLabel *l1 = new QLabel, *l2 = new QLabel;

	l1->setText("Система администрирования театров");
	l2->setText("<Подпись мелким шрифтом>");

	l1->setStyleSheet("font: 20pt Segoe UI");
	l2->setStyleSheet("font: 12pt Segoe UI");

	l1->setAlignment(Qt::AlignCenter);
	l2->setAlignment(Qt::AlignCenter);

	l->setAlignment(Qt::AlignVCenter);
	l->addWidget(l1);
	l->addWidget(l2);

	r->setLayout(l);

	return r;
}

