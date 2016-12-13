#include "actors.h"
#include <utils/TDB.h>
#include <QtCore>

actors::actors() {
	add = new QPushButton("Добавить новый");
	TDB db;
	QJsonArray ar = db.request("actors").toArray();


	l = new QVBoxLayout;
	l->addWidget(add);

	for (auto v : ar) {
		QWidget *n = new actor(v.toObject());
		l->addWidget(n);
		qDebug() << v;
	}

	setLayout(l);
}
