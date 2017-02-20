#include <utils/TDB.h>
#include <QtCore/QJsonArray>
#include <QtCore/QTimer>
#include <QtWidgets/QScrollArea>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtConcurrent/QtConcurrent>
#include "TMainMenu.h"

TMainMenu::TMainMenu(TMainWindow *w) : wnd(w) {
	l_main = new QVBoxLayout;
	l_menu = new QVBoxLayout;

	b_hide = new QPushButton(tr("Свернуть меню <"));

	QTimer::singleShot(50, this, &TMainMenu::reformMenu);

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
	menuStructure = QJsonArray();

	QStringList perms = TDB().getPerms();
//		 	"theatres",
//            "theatre_choose",
//			"theatre_create",
//			"theatre_edit",
//			"theatre_delete",
//
//			"users",
//			"user_create",
//			"user_edit",
//			"user_delete",
//
//			"actors",
//			"actor_create",
//			"actor_edit",
//			"actor_delete",
//
//			"perfs",
//			"perf_create",
//			"perf_edit",
//			"perf_delete",
//
//			"posters",
//			"poster_create",
//			"poster_edit",
//			"poster_delete",
//
//			"articles",
//			"article_create",
//			"article_edit",
//			"article_delete"
//	}; //TDB().getPerms();

	Ie("theatres");
		IeSI("theatres_choose", "Сменить текущий театр");
		IeSI("theatres_create", "Создать новый театр");
	IeC("theatres", "Театры");

	Ie("theatres_update");
	IeC("theatres_update", "Редактировать текущий театр");

	Ie("t_halls");
		IeSI("t_halls_update", "Изменить зал");
		IeSI("t_halls_create", "Создать новый зал");
	IeC("t_halls", "Залы");

	Ie("t_perfs");
		IeSI("t_perfs_create", "Добавление спектакля");
		IeSI("t_perfs_update", "Редактирование спектактля");
	IeC("t_perfs", "Репертуар");

	Ie("posters");
		IeSI("posters_create", "Добавление афиши");
		IeSI("posters_update", "Редактирование афиши");
	IeC("posters", "Афиша");

	Ie("articles");
		IeSI("articles_create", "Добавление статьи");
		IeSI("articles_update", "Редактирование статьи");
	IeC("articles", "Новости");

	Ie("actors");
		IeSI("actors_create", "Добавление актеров");
		IeSI("actors_update", "Редактирование данных об актере");
	IeC("actors", "Актеры");

	Ie("u_apis");
		IeSI("u_apis_create", "Добавление сотрудника");
		IeSI("u_apis_update", "Редактирование данных о сотруднике");
	IeC("u_apis", "Сотрудники");

	menuStructure << QJsonObject{{"action", ""},
	                             {"name",   ""},
	                             {"sub",    QJsonArray{}}};

	menuStructure << QJsonObject{{"action", "deleted"},
	                             {"name",   "Отобразить удаленные"},
	                             {"sub",    QJsonArray{}}};

	menuStructure << QJsonObject{{"action", "settings"},
	                             {"name",   "Настройки пользователя"},
	                             {"sub",    QJsonArray{}}};

	menuStructure << QJsonObject{{"action", "logout"},
	                             {"name",   "Сменить пользователя"},
	                             {"sub",    QJsonArray{}}};

	QJsonValue w = TDB().request("auth_api/get_settings", {{"key", "main_widget"}});
	wnd->changeCurrent(w.isNull() ? "main" : w.toString());
}

void TMainMenu::reformMenu() {
	createStructure();

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

