#ifndef THEATRE_ADMIN_TUSERCREATE_H
#define THEATRE_ADMIN_TUSERCREATE_H
#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>

class TUserCreate : public TCreate {
	QLineEdit *l_fio, *l_pos, *l_login, *l_passw, *l_phone;
	TCheckBox *l_perms;

public:
	TUserCreate();

	virtual void create();

	virtual void reset();

};


#endif //THEATRE_ADMIN_TUSERCREATE_H
