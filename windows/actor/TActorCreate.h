#ifndef THEATRE_ADMIN_TACTORCREATE_H
#define THEATRE_ADMIN_TACTORCREATE_H
#include <QtWidgets/QtWidgets>
#include <templates/TCreate.h>
#include <utils/TFileUpload.h>


class TActorCreate : public TCreate {
	QLineEdit *name;
	QTextEdit *desc;
	TFileUpload *img;

public:
	TActorCreate();

	virtual void reset() override;

	QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif // THEATRE_ADMIN_TACTORCREATE_H
