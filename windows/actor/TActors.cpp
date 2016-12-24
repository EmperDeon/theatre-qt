#include "TActors.h"
#include <utils/TDB.h>
#include <QtCore>

TActors::TActors() {
	add = new QPushButton("Добавить новый");
	TDB db;
	QJsonArray ar = db.request("actors").toArray();

	for (QJsonValue v : ar) {
		QWidget *n = new TActor(v.toObject());
		layout->addWidget(n);
	}
}
