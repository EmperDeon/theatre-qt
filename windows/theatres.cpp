#include "theatres.h"
#include <utils/TDB.h>
#include <QtCore>

theatres::theatres() {
	add = new QPushButton("Добавить новый");
	TDB db;
	QJsonArray ar = db.request("theatres").toArray();

	layout->addWidget(add);

	for (QJsonValue v : ar) {
		QWidget *n = new theatre(v.toObject());
		layout->addWidget(n);
	}
}
