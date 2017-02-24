#ifndef THEATRE_ADMIN_TheatreEdit_H
#define THEATRE_ADMIN_TheatreEdit_H
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>
#include <utils/TListBox.h>
#include <utils/TFileUpload.h>

class TTheatreEdit : public TEdit {
	QLineEdit *name, *phone, *address;
	QTextEdit *desc;
	TFileUpload *img;

	TListBox *halls;

public:
	TTheatreEdit();

	virtual void reset();

	virtual QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_TBOOKING_H
