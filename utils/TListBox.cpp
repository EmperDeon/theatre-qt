#include <QtCore/QJsonArray>
#include <dialogs/TDCheck.h>
#include "TListBox.h"
#include "TDB.h"

TListBox::TListBox(QString t) {
	QJsonArray a = TDB().request("lists/" + t).toArray();

	for (QJsonValue v : a) {
		map.insert(v.toObject()["name"].toString(), QString::number(v.toObject()["id"].toInt()));
	}
}

void TListBox::mouseDoubleClickEvent(QMouseEvent *event) {
	QStringList t = TDCheck::getSelection(map, selected);

	if (t.count() == 1 && t[0] == "") return;

	setIds(t);
}

void TListBox::setIds(QStringList l) {
	selected = l;

	this->clear();
	for (QString v : map.keys()) {
		if (l.contains(map[v]))
			this->addItem(v);
	}

}
