#include <utils/TDB.h>
#include <QtCore/QJsonArray>
#include <QtCore/QTimer>
#include <QtWidgets/QScrollArea>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include "TMainMenu.h"

TMainMenu::TMainMenu(TMainWindow *w) : wnd(w) {
	l_main = new QVBoxLayout;
	l_menu = new QVBoxLayout;

	b_hide = new QPushButton(tr("Свернуть меню <"));

	createStructure();
	reformMenu();

	connect(b_hide, &QPushButton::clicked, this, &TMainMenu::hideMenu);

	l_main->addWidget(b_hide);

	// Scroll
	QWidget *menu = new QWidget;
	menu->setLayout(l_menu);
	menu_s = new QScrollArea;
	e_menu = new QGraphicsOpacityEffect;

	menu_s->setFrameShape(QFrame::NoFrame);
	menu_s->setWidget(menu);
	menu_s->setWidgetResizable(true);
	menu_s->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	menu_s->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	menu_s->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	menu_s->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	menu->setGraphicsEffect(e_menu);

	l_main->addWidget(menu_s);

	l_main->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	l_menu->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	l_menu->setSizeConstraint(QLayout::SetMinAndMaxSize);

	this->setLayout(l_main);
	this->setFixedWidth(220);
}

void TMainMenu::entryClick(QString name) {
	wnd->changeCurrent(name);
//	qDebug() << name;
}

void TMainMenu::hideMenu() {
	bool v = !menu_s->isVisible();
	if (v) menu_s->setVisible(v);

	QPropertyAnimation
			*anim1 = new QPropertyAnimation(e_menu, "opacity"),
			*anim3 = new QPropertyAnimation(this, "maximumWidth"),
			*anim4 = new QPropertyAnimation(this, "minimumWidth");

	int width = 200;

	anim1->setDuration(width);
	anim3->setDuration(width);
	anim4->setDuration(width);

	anim1->setStartValue(v ? 0.0f : 1.0f);
	anim1->setEndValue(v ? 1.0f : 0.0f);

	anim3->setStartValue(v ? 50 : width);
	anim4->setStartValue(v ? 50 : width);

	anim3->setEndValue(v ? width : 50);
	anim4->setEndValue(v ? width : 50);

	QParallelAnimationGroup *group = new QParallelAnimationGroup;
	group->addAnimation(anim1);
	group->addAnimation(anim3);
	group->addAnimation(anim4);

	group->start();

	connect(group, &QParallelAnimationGroup::finished, [=]() {
		this->menu_s->setVisible(v);
		this->b_hide->setText(v ? "Скрыть меню <" : ">");
		this->setFixedWidth(v ? width : 50);
	});

}

// Add new begin (Insert entry)
#define Ie(a) if(perms.contains(a)){ \
                QJsonArray s

// Add sub entry (Insert entry Sub if)
#define IeSI(a, b) if(perms.contains( a )) \
                    s << QJsonObject{ \
                        {"action", a}, \
                        {"name", b} \
                    }

// Add new end
#define IeC(a, b)   menuStructure << QJsonObject{ \
                    {"action", a}, \
                    {"name", b}, \
                    {"sub", s} \
                    }; \
                   }


void TMainMenu::createStructure() {
	QStringList perms = {"theatres",
	                     "performances",
	                     "articles",
	                     "actors",
	                     "users",
	                     "edit_theatre",
	                     "edit_theatre",
	                     "edit_poster",
	                     "edit_perf",
	                     "edit_article",
	                     "edit_actors",
	                     "edit_user",
	                     "create_theatre",
	                     "create_poster",
	                     "create_perf",
	                     "create_article",
	                     "create_actors",
	                     "create_user"

	}; //TDB().getPerms();

	Ie("theatres");
		IeSI("create_theatre", "Создать новый театр");
		IeSI("edit_theatre", "Редактировать театр");
	IeC("theatres", "Театры");

	Ie("performances");
		IeSI("create_poster", "Добавление афиши");
		IeSI("edit_poster", "Редактирование афиши");
		IeSI("create_perf", "Добавление постановки");
		IeSI("edit_perf", "Редактирование постановки");
	IeC("performances", "Репертуар");

	Ie("articles");
		IeSI("create_article", "Добавление статьи");
		IeSI("edit_article", "Редактирование статьи");
	IeC("articles", "Новости");

	Ie("actors");
		IeSI("create_actors", "Добавление актеров");
		IeSI("edit_actors", "Редактирование данных об актере");
	IeC("actors", "Актеры");

	Ie("users");
		IeSI("create_user", "Добавление сотрудника");
		IeSI("edit_user", "Редактирование данных о сотруднике");
	IeC("users", "Сотрудники");

}

void TMainMenu::reformMenu() {
	QLayoutItem *item;
	while ((item = l_menu->takeAt(0)) != nullptr)
		item->widget()->deleteLater();

	for (QJsonValue i : menuStructure) {
		QJsonObject o = i.toObject();

		QLabel *nl = getNewMenuLabel(o, false);

		l_menu->addWidget(nl);

		for (QJsonValue j : o["sub"].toArray()) {
			QJsonObject s = j.toObject();

			QLabel *sl = getNewMenuLabel(s, true);
			l_menu->addWidget(sl);
		}
	}
}

QLabel *TMainMenu::getNewMenuLabel(QJsonObject o, bool sub) const {
	QLabel *r = new QLabel;

	r->setText("<a style=\"text-decoration: none; \" href='" + o["action"].toString() + "'>" + o["name"].toString() +
	           "</a>");
	r->setProperty("menuLink", sub);
	r->setWordWrap(true);
	r->setFixedWidth(200);
	connect(r, &QLabel::linkActivated, this, &TMainMenu::entryClick);

	return r;
}

