#include "actors.h"
#include <utils/TDB.h>
#include <QtCore>

actors::actors() {
	add = new QPushButton("Добавить новый");
	TDB db;
	QJsonArray ar = db.request("actors").toArray();

	for (auto v : ar) {
		QWidget *n = new actor(v.toObject());
		layout->addWidget(n);
	}
}
