#ifndef THEATRE_ADMIN_TUSER_H
#define THEATRE_ADMIN_TUSER_H
#include <utils/TCheckBox.h>
#include <templates/TTModel.h>

class TUser : public TTModel {
	QLineEdit *l_fio, *l_pos, *l_login, *l_phone;

public:
	TUser(QJsonObject o);

	virtual QString getPath() override;

	virtual void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_TUSER_H
