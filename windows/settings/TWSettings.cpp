#include <utils/TDB.h>
#include "TWSettings.h"
#include <windows/user/TUsers.h>

TWSettings::TWSettings() {
	QVBoxLayout *l = new QVBoxLayout;

	// Setting fields
	QFormLayout *fl = new QFormLayout;

	s_main_w = new QComboBox;

	fillMainW();

	fl->addRow("Окно, отображаемое первым", s_main_w);
	// Setting fields

	QHBoxLayout *hl = new QHBoxLayout;
	QPushButton *b_sv = new QPushButton("Сохранить"), *b_rs = new QPushButton("Очистить");

	hl->addWidget(b_sv);
	hl->addWidget(b_rs);

	connect(b_sv, &QPushButton::clicked, this, &TWSettings::save);
	connect(b_rs, &QPushButton::clicked, this, &TWSettings::reset);


	l->addLayout(fl);
	l->addLayout(hl);

	setLayout(l);

	load();
}

void TWSettings::fillMainW() {
	QJsonArray perms = TUsers::getPerms();

	QMap <QString, QString> desc = {
			{"Список театров",        "theatres"},
			{"Список сотрудников",    "u_apis"},
			{"Список актеров",        "actors"},
			{"Список спектаклей",     "perfs"},
			{"Список афиш",           "posters"},
			{"Список залов",          "t_halls"},
			{"Список цен",            "t_prices"},
			{"Список новостей",       "articles"},
			{"Список спектаклей",     "t_perfs"},

			{"Создание театров",      "theatres_create"},
			{"Создание сотрудников",  "u_apis_create"},
			{"Создание актеров",      "actors_create"},
			{"Создание спектаклей",   "perfs_create"},
			{"Создание афиш",         "posters_create"},
			{"Создание новостей",     "articles_create"},
			{"Создание спектаклей",   "t_perfs_create"},
			{"Создание залов",        "t_halls_create"},
			{"Создание цен",          "t_prices_create"},

			{"Изменение театров",     "theatres_update"},
			{"Изменение сотрудников", "u_apis_update"},
			{"Изменение актеров",     "actors_update"},
			{"Изменение спектаклей",  "perfs_update"},
			{"Изменение афиш",        "posters_update"},
			{"Изменение залов",       "t_halls_update"},
			{"Изменение цен",         "t_prices_update"},
			{"Изменение новостей",    "articles_update"},
			{"Изменение спектаклей",  "t_perfs_update"},

			{"Выбор текущего театра", "theatre_choose"}
	};

	s_main_w->clear();

	for (QString k : desc.keys()) {
		QString d = desc[k];
		d.replace(QRegExp("create|update|destroy|restore"), "edit");

		if (perms.contains(d))
			s_main_w->addItem(k, desc[k]);
	}
}

void TWSettings::load() {
//	sett = TDB().request("auth_api/get_settings").toObject();
//
//	sett["main_widget"] = s_main_w->currentData().toString(); TODO: Work with it. Dunno how can i select item by perm
}

void TWSettings::save() {
	sett["main_widget"] = s_main_w->currentData().toString();

	TDB().request("auth_api/set_settings", {{"settings", QJsonDocument(sett).toJson(QJsonDocument::Compact)}});
}

void TWSettings::reset() {

}
