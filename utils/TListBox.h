#ifndef THEATRE_ADMIN_TLISTBOX_H
#define THEATRE_ADMIN_TLISTBOX_H

#include <QtWidgets/QtWidgets>


class TListBox : public QGroupBox {
	QMap<QString, QString> map;

	QListWidget *list;

	QStringList added, removed;

	void add();

	void rem();

public:
	TListBox(QString t = "");

	void load(QString t);

	QString getAdded();

	QString getItems();
};


#endif //THEATRE_ADMIN_TLISTBOX_H
