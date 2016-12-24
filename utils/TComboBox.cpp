#include <QtCore/QJsonArray>
#include "TComboBox.h"
#include "TDB.h"


TComboBox::TComboBox(QString table) {
	if (table != "")
		load(table);
}

void TComboBox::load(QString table) {
	QJsonArray obj = TDB().request("lists/" + table).toArray();

	for (QJsonValue v : obj) {
		map.insert(v.toObject()["id"].toInt(), v.toObject()["name"].toString());
	}

	setLists();
}

void TComboBox::setLists() {
	this->addItems(map.values());
}

QString TComboBox::getIndex() const {
	return QString::number(map.keys().value(this->currentIndex()));
}

void TComboBox::setCurrentItem(int id) {
	setCurrentIndex(map.keys().indexOf(id));
}
