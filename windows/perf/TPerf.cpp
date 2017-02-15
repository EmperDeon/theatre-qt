#include <utils/TDB.h>
#include "TPerf.h"

TPerf::TPerf(QJsonObject o) : TTModel(o) {
	l_name = new QLineEdit(o["perf"].toObject()["name"].toString());
	l_auth = new QLineEdit(o["perf"].toObject()["author"].toString());
	l_type = new QLineEdit(o["type"].toObject()["name"].toString());
	e_desc_s = new QTextEdit(o["desc_s"].toString());

	l_name->setEnabled(false);
	l_auth->setEnabled(false);
	l_type->setEnabled(false);

	e_desc_s->setEnabled(false);
	e_desc_s->setMaximumHeight(100);

	layout->addRow("Название:", l_name);
	layout->addRow("Автор:", l_auth);
	layout->addRow("Тип:", l_type);
	layout->addRow("Краткое описание:", e_desc_s);
}

QString TPerf::getPath() {
	return "t_perfs";
}

void TPerf::setFEnabled(bool b) {
	e_desc_s->setEnabled(b);
}

QMap<QString, QString> TPerf::getParams() {
	return {
			{"id",     QString::number(id)},
			{"desc_s", e_desc_s->toPlainText()}
	};
}