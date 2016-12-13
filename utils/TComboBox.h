#ifndef THEATRE_ADMIN_TCOMBOBOX_H
#define THEATRE_ADMIN_TCOMBOBOX_H

#include <QtWidgets/QComboBox.h>
#include <QtCore/QJsonObject>

class TComboBox : public QComboBox {
	QList<int> l_ids;
	QStringList l_str;


public:
	TComboBox(QString table);

	void setLists();

	int getIndex() const;
};


#endif //THEATRE_ADMIN_TCOMBOBOX_H
