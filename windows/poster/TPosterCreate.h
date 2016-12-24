#ifndef TPOSTERCREATE_H
#define TPOSTERCREATE_H

#include <QtWidgets/QtWidgets>
#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>

class TPosterCreate : public TCreate {
	TComboBox *name;
	TComboBox *hall;
	QDateTimeEdit *date;

public:
	TPosterCreate();

	virtual void create();

	virtual void reset();

};


#endif // TPOSTERCREATE_H
