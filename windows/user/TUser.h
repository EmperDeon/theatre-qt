#ifndef THEATRE_ADMIN_TUSER_H
#define THEATRE_ADMIN_TUSER_H

#include <utils/TCheckBox.h>
#include <QtCore/QJsonObject>
#include <QtWidgets/QtWidgets>

class TUser : public QFrame {
	int id;
	QLineEdit *l_fio, *l_pos, *l_login, *l_phone;
	QPushButton *b_edt, *b_del;

public:
	TUser(QJsonObject o);

	void edt();

	void del();

	void save();
};


#endif //THEATRE_ADMIN_TUSER_H
