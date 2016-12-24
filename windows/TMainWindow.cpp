#include <QtWidgets/QHBoxLayout>
#include <utils/TConfig.h>
#include "windows/TChoose.h"
#include "TMainWindow.h"

#include <windows/article/TArticles.h>
#include <windows/article/TArticleEdit.h>
#include <windows/article/TArticleCreate.h>

#include <windows/perf/TPerfs.h>
#include <windows/perf/TPerfCreate.h>
#include <windows/perf/TPerfEdit.h>

#include <windows/poster/TPosters.h>
#include <windows/poster/TPosterCreate.h>
#include <windows/poster/TPosterEdit.h>

#include "windows/theatre/TTheatreCreate.h"
#include "windows/theatre/TTheatreEdit.h"
#include "windows/theatre/TTheatres.h"

#include <windows/user/TUsers.h>
#include <windows/user/TUserCreate.h>
#include <windows/user/TUserEdit.h>


TMainWindow::TMainWindow() {
	QWidget *nw = new QWidget;
	l = new QHBoxLayout;
	w_menu = new TMainMenu(this);

	l->setContentsMargins(0, 0, 0, 0);

	l->addWidget(w_menu);

	nw->setLayout(l);
	this->setCentralWidget(nw);

	changeCurrent("main");
	resize(1000, 500);
}

void TMainWindow::changeCurrent(QString s) {
	if (w_curr != nullptr)
		w_curr->deleteLater(), w_curr = nullptr;

	if (s == "logout") {
		TConfig conf;
		conf.rem("token");
		conf.save();
		changeCurrent("main");

		QTimer::singleShot(100, [=]() {
			w_menu->reformMenu();
		});

	} else if (s == "main") {
		w_curr = getNewMainWidget();

	} else if (s == "theatre_create") {
		w_curr = new TTheatreCreate;

	} else if (s == "theatre_edit") {
		w_curr = new TTheatreEdit;

	} else if (s == "theatres") {
		w_curr = new TTheatres;

	} else if (s == "users") {
		w_curr = new TUsers;

	} else if (s == "user_create") {
		w_curr = new TUserCreate;

	} else if (s == "user_edit") {
		w_curr = new TUserEdit;

	} else if (s == "articles") {
		w_curr = new TArticles;

	} else if (s == "article_edit") {
		w_curr = new TArticleEdit;

	} else if (s == "article_create") {
		w_curr = new TArticleCreate;

	} else if (s == "theatre_choose") {
		w_curr = new TChoose;

	} else if (s == "t_perfs") {
		w_curr = new TPerfs;

	} else if (s == "t_perf_create") {
		w_curr = new TPerfCreate;

	} else if (s == "t_perf_edit") {
		w_curr = new TPerfEdit;

	} else if (s == "posters") {
		w_curr = new TPosters;

	} else if (s == "poster_create") {
		w_curr = new TPosterCreate;

	} else if (s == "poster_edit") {
		w_curr = new TPosterEdit;

	}


	s_curr = s;
	if (w_curr != nullptr)
		l->addWidget(w_curr);
	else
		w_curr = new QLabel("No Widget"), l->addWidget(w_curr, Qt::AlignCenter);
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

