#ifndef THEATRE_ADMIN_THALLCREATE_H
#define THEATRE_ADMIN_THALLCREATE_H

#include <QtWidgets>
#include <templates/TCreate.h>
#include "windows/hall/draw/THall.h"

class THallCreate : public QWidget {
	THall *hall;

	QLineEdit *l_h_w, *l_h_h, *l_h_n;

public:
	THallCreate();

	QString getPath();

	QMap<QString, QString> getParams();

	void reset();

	void save();

	void setSize();
};


#endif //THEATRE_ADMIN_THALLCREATE_H
