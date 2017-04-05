#ifndef THEATRE_ADMIN_TCHECKBOX_H
#define THEATRE_ADMIN_TCHECKBOX_H

#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>

class TCheckBox;

class TCheckBox : public QWidget {
	QMap<QString, QString> map;
	QStringList selected;

	QList<QCheckBox *> lst;

public:
	TCheckBox(QString t);

	void clearList() { selected.clear(); }

	void setIds(QJsonArray l);

	QString getIds();

	void clear();

	QString tryDescribe(QString n);

	QString tryDeDescribe(QString n);
};


#endif //THEATRE_ADMIN_TCHECKBOX_H
