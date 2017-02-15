#ifndef TPOSTEREDIT_H
#define TPOSTEREDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>

class TPosterEdit : public TEdit {
	TComboBox *name;
	QDateTimeEdit *date;


public:
	TPosterEdit();

	virtual void reset();

	virtual QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif // TPOSTEREDIT_H


