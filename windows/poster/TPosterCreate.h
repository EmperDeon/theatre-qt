#ifndef TPOSTERCREATE_H
#define TPOSTERCREATE_H

#include <QtWidgets/QtWidgets>
#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>

class TPosterCreate : public TCreate {
	TComboBox *name;
	QDateTimeEdit *date;
	QLabel *l_prices;
	QString price = "";

public:
	TPosterCreate();

	void setHalls();

	virtual void reset();

	QString getPath() override;

	QMap<QString, QString> getParams() override;

};


#endif // TPOSTERCREATE_H
