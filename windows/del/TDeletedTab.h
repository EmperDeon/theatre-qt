#ifndef THEATRE_ADMIN_TDELETEDTAB_H
#define THEATRE_ADMIN_TDELETEDTAB_H

#include <QtWidgets/QtWidgets>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <templates/TTModels.h>

class TDeletedTab : public TTModels {
	QJsonArray o_del;

public:
	TDeletedTab(QString p, QJsonArray o);

};

class TDeletedTabW : public QFrame { // Inner widget
	QString id, path;

public:
	TDeletedTabW(QString p, QJsonObject o);

	void restore();

	QString getDesc(QString k);
};


#endif //THEATRE_ADMIN_TDELETEDTAB_H
