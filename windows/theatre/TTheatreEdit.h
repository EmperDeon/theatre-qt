#ifndef THEATRE_ADMIN_edit1theatre_H
#define THEATRE_ADMIN_edit1theatre_H

#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>
#include <utils/TListBox.h>

class TTheatreEdit : public TEdit {
	QTextEdit *desc;
	QLineEdit *name;
	QLineEdit *phone;
	QLineEdit *address;

	TListBox *list;

public:
	TTheatreEdit();

	virtual void submit();

	virtual void reset();

	virtual void load();
};


#endif //THEATRE_ADMIN_TBOOKING_H
