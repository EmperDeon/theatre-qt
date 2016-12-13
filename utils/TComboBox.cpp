#include <QtCore/QJsonArray>
#include "TComboBox.h"
#include "TDB.h"


TComboBox::TComboBox(QString table) {
	QJsonArray obj = TDB().request("lists/" + table).toArray();

	for (auto v : obj) {
		l_ids << v.toObject()["id"].toInt();
		l_str << v.toObject()["name"].toString();
	}

	setLists();
}

void TComboBox::setLists() {
	this->addItems(l_str);
}

int TComboBox::getIndex() const {
	return l_ids.value(this->currentIndex());
}
