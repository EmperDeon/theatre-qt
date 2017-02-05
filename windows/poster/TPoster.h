#ifndef TPOSTER_H
#define TPOSTER_H
#include <utils/TComboBox.h>
#include <templates/TTModel.h>


class TPoster : public TTModel {
	QLineEdit *l_name, *l_hall;
	QDateTimeEdit *l_date;

public:
	TPoster(QJsonObject o);

	virtual QString getPath() override;

	virtual void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;
};


#endif // TPOSTER_H
