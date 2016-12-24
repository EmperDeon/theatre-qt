#ifndef THEATRE_ADMIN_TCOMBOBOX_H
#define THEATRE_ADMIN_TCOMBOBOX_H
#include <QtWidgets/QComboBox.h>

class TComboBox : public QComboBox {
	QMap<int, QString> map;

public:
	TComboBox(QString table = "");

	void load(QString table);
	void setLists();

	void setCurrentItem(int id);
	QString getIndex() const;
};


#endif //THEATRE_ADMIN_TCOMBOBOX_H
