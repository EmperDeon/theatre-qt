#include <utils/TDB.h>
#include "TDeletedTab.h"

TDeletedTab::TDeletedTab(QString p, QJsonArray o) : o_del(o) {
	for (QJsonValue v : o_del) {
		TDeletedTabW *n = new TDeletedTabW(p, v.toObject());

		layout->addWidget(n);
	}
}

TDeletedTabW::TDeletedTabW(QString p, QJsonObject o) : path(p) {
	QFormLayout *l = new QFormLayout;

	id = QString::number(o.take("id").toInt());

	// Bottom timestamps and button
	QHBoxLayout *l_info = new QHBoxLayout;
	QLabel *i_upd = new QLabel("Обновлено: " + o.take("updated_at").toString()),
			*i_del = new QLabel("Удалено: " + o.take("deleted_at").toString());
	QPushButton *i_res = new QPushButton("Восстановить");

	l_info->addWidget(i_upd);
	l_info->addWidget(i_del);
	l_info->addWidget(i_res);

	connect(i_res, &QPushButton::clicked, this, &TDeletedTabW::restore);
	// Bottom timestamps and button

	// Remove unused fields
	o.remove("created_at");

	for (QString k : o.keys()) {
		QString name = getDesc(k), val;
		QJsonValue v = o[k];

		if (v.isString()) {
			val = v.toString();

		} else if (v.isDouble()) {
			val = QString::number(v.toInt());

		} else if (v.isNull()) {
			val = "NULL";

		} else {
			qDebug() << "Error: " << v;
		}

		QWidget *w;
		if (val.size() > 100) {
			w = new QTextEdit(val);

		} else {
			w = new QLineEdit(val);
		}


		l->addRow(name, w);
	}

	l->addRow(l_info);

	setLayout(l);
	setFrameStyle(QFrame::StyledPanel);
}

void TDeletedTabW::restore() {
	TDB().request(path + "/restore", {{"id", id}});

	this->deleteLater();
}

QString TDeletedTabW::getDesc(QString k) {
	return k;
}
