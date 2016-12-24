#ifndef THEATRE_ADMIN_TUSEREDIT_H
#define THEATRE_ADMIN_TUSEREDIT_H
#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>

class TUserEdit : public TEdit {
	QLineEdit *l_fio, *l_pos, *l_login, *l_passw, *l_phone;
	TCheckBox *l_perms;

public:
	TUserEdit();

	virtual void submit();

	virtual void reset();

	virtual void load();
};


#endif //THEATRE_ADMIN_TUSEREDIT_H
