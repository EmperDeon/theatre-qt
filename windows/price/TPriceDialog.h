#ifndef THEATRE_ADMIN_TPRICECREATE_H
#define THEATRE_ADMIN_TPRICECREATE_H

#include <QtWidgets>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>
#include "windows/price/draw/THallPrice.h"

class TPriceDialog : public QDialog {
	THallPrice *price;

public:
	TPriceDialog(int hall_id, QJsonObject o = QJsonObject());

	static QString getPrice(int hall_id, QJsonObject o = QJsonObject());
};


#endif //THEATRE_ADMIN_TPRICECREATE_H
