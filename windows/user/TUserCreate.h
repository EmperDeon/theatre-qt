#ifndef THEATRE_ADMIN_TUSERCREATE_H
#define THEATRE_ADMIN_TUSERCREATE_H

#include <QtWidgets/QtWidgets>
#include <utils/TListBox.h>

class TUserCreate : public QWidget {
	QPushButton *b_create, *b_reset;

	QLineEdit *l_fio, *l_pos, *l_login, *l_passw, *l_phone;
	TListBox *l_perms;

public:
	TUserCreate();

	void create();

	void reset();

};


#endif //THEATRE_ADMIN_TUSERCREATE_H
