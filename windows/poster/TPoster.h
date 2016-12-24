#ifndef TPOSTER_H
#define TPOSTER_H

#include <QtWidgets/QtWidgets>
#include <QtCore/QJsonObject>
#include <utils/TComboBox.h>

class TPoster : public QWidget {
	QPushButton *b_edt;
	QPushButton *b_del;
	int id;

	QLineEdit *l_name, *l_hall;
	QDateTimeEdit *l_date;

public:
	TPoster(QJsonObject o);

	void edt();

	void save();

	void del();
};


#endif // TPOSTER_H
