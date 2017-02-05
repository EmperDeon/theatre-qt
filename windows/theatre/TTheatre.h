#ifndef THEATRE_H
#define THEATRE_H
#include <utils/TDB.h>
#include <templates/TTModel.h>

class TTheatre : public TTModel {
	QLineEdit *name, *address, *phone;
	QTextEdit *desc;

public:
	TTheatre(QJsonObject o);

	virtual QString getPath() override;

	virtual void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;
};


#endif // THEATRE_H
