#ifndef THEATRE_ADMIN_TPRICECREATE_H
#define THEATRE_ADMIN_TPRICECREATE_H

#include <QtWidgets>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>
#include "windows/price/draw/THallPrice.h"

class TPriceCreate : public QWidget {
	THallPrice *price;

	TComboBox *c_poster, *c_hall;

public:
	TPriceCreate();

	QString getPath();

	QMap<QString, QString> getParams();

	void reset();

	void save();

	void selectHall(int n);
};


#endif //THEATRE_ADMIN_TPRICECREATE_H
