#ifndef THEATRE_ADMIN_TACTOR_H
#define THEATRE_ADMIN_TACTOR_H
#include <QtWidgets/QtWidgets>
#include <templates/TTModel.h>


class TActor : public TTModel {
	QLineEdit *name;
	QTextEdit *desc;

public:
	TActor(QJsonObject o);

	virtual QString getPath() override;

	virtual void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;

};

#endif // THEATRE_ADMIN_TACTORS_H
