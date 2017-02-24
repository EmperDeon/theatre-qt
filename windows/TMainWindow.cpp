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

#include <windows/theatre/TTheatreCreate.h>
#include <windows/theatre/TTheatreEdit.h>
#include <windows/theatre/TTheatres.h>

#include <windows/user/TUsers.h>
#include <windows/user/TUserCreate.h>
#include <windows/user/TUserEdit.h>
#include <windows/hall/THallCreate.h>
#include <windows/hall/THalls.h>
#include <windows/del/TDeleted.h>
#include <windows/settings/TWSettings.h>
#include <windows/actor/TActors.h>
#include <windows/actor/TActorCreate.h>
#include <windows/actor/TActorEdit.h>


TMainWindow::TMainWindow() {
	QWidget *nw = new QWidget;
	l = new QHBoxLayout;
	w_menu = new TMainMenu(this);
	l_status = new QLabel;

	l->setContentsMargins(0, 0, 0, 0);

	l->addWidget(w_menu);

	nw->setLayout(l);
	this->setCentralWidget(nw);

	resize(800, 500);

	this->statusBar()->addPermanentWidget(l_status);
}

void TMainWindow::changeCurrent(QString s) {
	if (loadingWidget) { // Exit if already loading
		return;
	}

	if (w_curr != nullptr)
		w_curr->setVisible(false), w_curr->deleteLater(), w_curr = nullptr;

	loadingWidget = true;
	auto loadW = getNewLoadWidget();
	l->addWidget(loadW);



	if (s == "logout") {
		TConfig conf;
		conf.rem("token");
		conf.save();
		changeCurrent("main");

		QTimer::singleShot(100, [=]() {
			w_menu->reformMenu();
		});

	} else if (s == "main") {
//		w_curr = getNewMainWidget();
		w_curr = new THallCreate;

	} else if (s == "deleted") {
		w_curr = new TDeleted;

	} else if (s == "settings") {
		w_curr = new TWSettings;

	} else if (s == "theatres_create") {
		w_curr = new TTheatreCreate;

	} else if (s == "theatres_update") {
		w_curr = new TTheatreEdit;

	} else if (s == "theatres") {
		w_curr = new TTheatres;

	} else if (s == "t_halls") {
		w_curr = new THalls;

	} else if (s == "u_apis") {
		w_curr = new TUsers;

	} else if (s == "u_apis_create") {
		w_curr = new TUserCreate;

	} else if (s == "u_apis_update") {
		w_curr = new TUserEdit;

	} else if (s == "articles") {
		w_curr = new TArticles;

	} else if (s == "articles_update") {
		w_curr = new TArticleEdit;

	} else if (s == "articles_create") {
		w_curr = new TArticleCreate;

	} else if (s == "theatres_choose") {
		w_curr = new TChoose;

	} else if (s == "t_perfs") {
		w_curr = new TPerfs;

	} else if (s == "t_perfs_create") {
		w_curr = new TPerfCreate;

	} else if (s == "t_perfs_update") {
		w_curr = new TPerfEdit;

	} else if (s == "posters") {
		w_curr = new TPosters;

	} else if (s == "posters_create") {
		w_curr = new TPosterCreate;

	} else if (s == "posters_update") {
		w_curr = new TPosterEdit;

	} else if (s == "actors") {
		w_curr = new TActors;

	} else if (s == "actors_create") {
		w_curr = new TActorCreate;

	} else if (s == "actors_update") {
		w_curr = new TActorEdit;

	}

	if (w_curr != nullptr) {
		l->addWidget(w_curr);
	} else {
		w_curr = new QLabel("No Widget"), l->addWidget(w_curr, Qt::AlignCenter);
	}

	loadW->deleteLater();
	loadingWidget = false;
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

QWidget *TMainWindow::getNewLoadWidget() {
	QWidget *w = new QWidget;
	QVBoxLayout *l = new QVBoxLayout;

	QLabel *l1 = new QLabel("Страница загружается, пожалуйста подождите");
	QLabel *l2 = new QLabel;

	l1->setStyleSheet("font: 16pt Segoe UI");

	QMovie *m = new QMovie(":/loading.gif");
	m->start();
	l2->setMovie(m);

	l->addWidget(l1);
	l->addWidget(l2, 0, Qt::AlignCenter);
	l->setAlignment(Qt::AlignCenter);
	l->setSpacing(40);

	w->setLayout(l);
	return w;
}

void TMainWindow::showStatusMessage(QString s) {
	l_status->setStyleSheet(QString("color: ") + (s.startsWith("Успешно") ? "green" : "red"));
	l_status->setText(s);

	QTimer::singleShot((s.startsWith("Успешно") ? 1500 : 5000), [=]() {
		l_status->clear();
	});
}
