#ifndef THEATRE_ADMIN_TACTOREDIT_H
#define THEATRE_ADMIN_TACTOREDIT_H

#include <QtWidgets/QtWidgets>
#include <templates/TEdit.h>
#include <utils/TFileUpload.h>


class TActorEdit : public TEdit {
	QTextEdit *desc;
	QLineEdit *name;
	TFileUpload *img;

public:
	TActorEdit();

	virtual void reset();

	virtual QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_TACTOREDIT_H
