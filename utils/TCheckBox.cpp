#include <QtCore/QJsonArray>
#include "TCheckBox.h"
#include "TDB.h"

TCheckBox::TCheckBox(QString t) {
	QJsonObject a = TDB().request("utils/lists/", {{"name", t}}).toObject();

	for (QString v : a.keys()) {
		map.insert(a[v].toString(), QString::number(v.toInt()));
	}

	QVBoxLayout *l = new QVBoxLayout;
	QHBoxLayout *hl1 = new QHBoxLayout;
	QStringList n = map.keys();

	int size = 6; // Size of column

	for (int i = 0; i < (n.count() / size) + 1; i++) {
		QVBoxLayout *tl = new QVBoxLayout;
		tl->setAlignment(Qt::AlignTop);

		for (int j = 0; j < size; j++) {
			if (n.count() > (i * size + j)) {
				QCheckBox *tc = new QCheckBox(tryDescribe(n[i * size + j]));
				tc->setChecked(selected.contains(map[n[i * size + j]]));

				tl->addWidget(tc);
				lst << tc;
			}
		}

		hl1->addLayout(tl);
	}

	l->addLayout(hl1);

	setLayout(l);
}

QString TCheckBox::getIds() {
	QJsonArray r;

	for (QCheckBox *v : lst)
		if (v->isChecked())
			r << map[v->text()].toInt();

	return QJsonDocument(r).toJson(QJsonDocument::Compact);
}

void TCheckBox::setIds(QJsonArray l) {
	selected.clear();

	for (QJsonValue v : l)
		selected << QString::number(v.toInt());

	for (QCheckBox *tc : lst) {
		tc->setChecked(selected.contains(map[tryDeDescribe(tc->text())]));
	}
}

void TCheckBox::clear() {
	selected.clear();

	for (QCheckBox *tc : lst)
		tc->setChecked(false);
}

QString TCheckBox::tryDescribe(QString n) {
	QMap<QString, QString> desc = {
			{"Список театров",                  "theatres"},
			{"Список сотрудников",              "u_apis"},
			{"Список актеров",                  "actors"},
			{"Список спектаклей",               "perfs"},
			{"Список афиш",                     "posters"},
			{"Список залов",                    "t_halls"},
			{"Список цен",                      "t_prices"},
			{"Список новостей",                 "articles"},
			{"Список спектаклей",               "t_perfs"},
			{"Список глобальных спектаклей",    "perfs"},
			{"Изменение глобальных спектаклей", "perfs_edit"},
			{"Изменение театров",               "theatres_edit"},
			{"Изменение сотрудников",           "u_apis_edit"},
			{"Изменение актеров",               "actors_edit"},
			{"Изменение спектаклей",            "perfs_edit"},
			{"Изменение афиш",                  "posters_edit"},
			{"Изменение залов",                 "t_halls_edit"},
			{"Изменение цен",                   "t_prices_edit"},
			{"Изменение новостей",              "articles_edit"},
			{"Изменение спектаклей",            "t_perfs_edit"},
			{"Выбор текущего театра",           "theatre_choose"}
	};

	for (QString k : desc.keys()) {
		if (desc[k] == n) {
			return k;
		}
	}

	return n;
}

QString TCheckBox::tryDeDescribe(QString n) {
	QMap<QString, QString> desc = {
			{"Список театров",                  "theatres"},
			{"Список сотрудников",              "u_apis"},
			{"Список актеров",                  "actors"},
			{"Список спектаклей",               "perfs"},
			{"Список афиш",                     "posters"},
			{"Список залов",                    "t_halls"},
			{"Список цен",                      "t_prices"},
			{"Список новостей",                 "articles"},
			{"Список спектаклей",               "t_perfs"},
			{"Список глобальных спектаклей",    "perfs"},
			{"Изменение глобальных спектаклей", "perfs_edit"},
			{"Изменение театров",               "theatres_edit"},
			{"Изменение сотрудников",           "u_apis_edit"},
			{"Изменение актеров",               "actors_edit"},
			{"Изменение спектаклей",            "perfs_edit"},
			{"Изменение афиш",                  "posters_edit"},
			{"Изменение залов",                 "t_halls_edit"},
			{"Изменение цен",                   "t_prices_edit"},
			{"Изменение новостей",              "articles_edit"},
			{"Изменение спектаклей",            "t_perfs_edit"},
			{"Выбор текущего театра",           "theatre_choose"}
	};

	return desc.contains(n) ? desc[n] : n;
}
