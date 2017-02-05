#ifndef THEATRE_ADMIN_TBOOKING_H
#define THEATRE_ADMIN_TBOOKING_H

#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>
#include <utils/TListBox.h>

class TTheatreCreate : public TCreate {
	QLineEdit *name, *phone, *address;
	QTextEdit *desc;

	TListBox *list;

public:
	TTheatreCreate();

	virtual void reset();

	QString getPath() override;

	QMap<QString, QString> getParams() override;

};

#endif //THEATRE_ADMIN_TBOOKING_H
