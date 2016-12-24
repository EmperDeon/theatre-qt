#ifndef TPOSTEREDIT_H
#define TPOSTEREDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>

class TPosterEdit : public TEdit {
	TComboBox *name, *hall;
	QDateTimeEdit *date;


public:
	TPosterEdit();

	virtual void submit();

	virtual void reset();

	virtual void load();
};


#endif // TPOSTEREDIT_H


