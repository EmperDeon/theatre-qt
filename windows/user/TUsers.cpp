#include "TUsers.h"
#include <utils/TDB.h>
#include <windows/user/TUser.h>

// TUsers
TUsers::TUsers() {
	QVBoxLayout *l = new QVBoxLayout;

	// Scroll
	QScrollArea *scroll = new QScrollArea;
	QWidget *w = new QWidget;
	QVBoxLayout *wl = new QVBoxLayout;

	wl->setMargin(0);
	wl->setAlignment(Qt::AlignTop);
	w->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	w->setLayout(wl);

	scroll->setWidget(w);
	scroll->setWidgetResizable(true);
	scroll->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
	scroll->setFrameStyle(QFrame::NoFrame);

	l->addWidget(scroll);

	// Fill scroll with widgets
	QJsonArray users = TDB().request("users").toArray();

	for (auto v : users)
		wl->addWidget(new TUser(v.toObject()));

	setLayout(l);
}
// TUsers