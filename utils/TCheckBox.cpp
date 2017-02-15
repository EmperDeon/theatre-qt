#include <QtCore/QJsonArray>
#include <dialogs/TDCheck.h>
#include "TCheckBox.h"
#include "TDB.h"

TCheckBox::TCheckBox(QString t) {
	QJsonObject a = TDB().request("utils/lists/", {{"name", t}}).toObject();

	for (QString v : a.keys()) {
		map.insert(a[v].toString(), QString::number(v.toInt()));
	}
}

void TCheckBox::mouseDoubleClickEvent(QMouseEvent *event) {
	Q_UNUSED(event);
	QStringList t = TDCheck::getSelection(map, selected);

	if (t.count() == 1 && t[0] == "") return;

	setIds(t);
}

void TCheckBox::setIds(QStringList l) {
	selected = l;

	this->clear();
	for (QString v : map.keys()) {
		if (l.contains(map[v]))
			this->addItem(v);
	}

}

QString TCheckBox::getIds() {
	QJsonArray r;

	for (QString s : selected)
		r << s.toInt();

	return QJsonDocument(r).toJson();
}

void TCheckBox::setIds(QJsonArray l) {
	selected.clear();

	for (QJsonValue v : l)
		selected << QString::number(v.toInt());

	this->clear();
	for (QString v : map.keys()) {
		if (l.contains(map[v]))
			this->addItem(v);
	}
}
