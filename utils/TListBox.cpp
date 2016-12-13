#include <QtCore/QJsonArray>
#include <dialogs/TDCheck.h>
#include "TListBox.h"
#include "TDB.h"

TListBox::TListBox(QString t) {
	QJsonArray a = TDB().request("lists/" + t).toArray();

	for (auto v : a) {
		map.insert(v.toObject()["name"].toString(), v.toObject()["id"].toInt());
	}


}

void TListBox::mouseDoubleClickEvent(QMouseEvent *event) {
	QList<int> t = TDCheck::getSelection(map, selected);

	if (t.count() == 1 && t[0] == -1) return;

	selected = t;

	this->clear();
	for (auto v : map.keys()) {
		if (t.contains(map[v]))
			this->addItem(v);
	}

}