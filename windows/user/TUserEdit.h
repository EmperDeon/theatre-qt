#ifndef THEATRE_ADMIN_TUSEREDIT_H
#define THEATRE_ADMIN_TUSEREDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TListBox.h>
#include <utils/TComboBox.h>

class TUserEdit : public QWidget {
Q_OBJECT
	int id;
	QJsonObject obj;
	TComboBox *c_box;
	QPushButton *b_create, *b_reset;

	QLineEdit *l_fio, *l_pos, *l_login, *l_passw, *l_phone;
	TListBox *l_perms;

public:
	TUserEdit();

	void submit();

	void reset();

public slots:

	void changeIndex(int i);
};


#endif //THEATRE_ADMIN_TUSEREDIT_H
