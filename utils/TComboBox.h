#ifndef THEATRE_ADMIN_TCOMBOBOX_H
#define THEATRE_ADMIN_TCOMBOBOX_H
#include <QtWidgets/QComboBox.h>

class TComboBox : public QComboBox {
	QMap<int, QString> map;

public:
	TComboBox(QString table);

	void setLists();

	QString getIndex() const;
};


#endif //THEATRE_ADMIN_TCOMBOBOX_H
