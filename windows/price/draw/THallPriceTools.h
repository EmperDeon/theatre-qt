#ifndef THEATRE_ADMIN_TPRICETOOLS_H
#define THEATRE_ADMIN_TPRICETOOLS_H

#include <windows/price/draw/THallPrice.h>

class THallPriceTools : public QWidget {
	QButtonGroup *bg;
	QHBoxLayout *l_price;

	QMap<int, TPriceSect> sect_list;
	QMap<int, TPriceSect> price_list;

public:
	THallPriceTools();

	void add();

	void edt();

	void updateSects();

	QMap<int, TPriceSect> getSectors();

	QMap<int, TPriceSect> getPrices();

	int getCurrentPrice();

	QJsonArray toJson();

	void fromJson(QJsonArray o);

	void loadHall(QJsonArray o);
};

class TPriceToolSect : public QDialog {
	QLineEdit *l_name, *l_pref;
	QColor l_color;

public:
	TPriceToolSect();

	static TPriceSect getSect(TPriceSect old = TPriceSect());

};

#endif //THEATRE_ADMIN_TPRICETOOLS_H
