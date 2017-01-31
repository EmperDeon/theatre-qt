#include <QtCore/QJsonArray>
#include "TComboBox.h"
#include "TDB.h"


TComboBox::TComboBox(QString table) {
	if (table != "")
		load(table);
}

void TComboBox::load(QString table) {
	QJsonObject obj = TDB().request("utils/lists", {{"name", table}}).toObject();

	for (QString v : obj.keys()) {
		map.insert(v.toInt(), obj[v].toString());
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
