#ifndef THEATRE_ADMIN_TUSER_H
#define THEATRE_ADMIN_TUSER_H

#include <QtWidgets>
#include <utils/TListBox.h>

class TUsers;

class TUser;

class TUserCreate;

class TUserEdit;

class TUserDelete;


class TUsers : public QWidget { // Отображение всех юзеров


public:
	TUsers();
};

class TUser : public QWidget {
	TListBox *c;


public:
	TUser(QJsonObject o);
};

class TUserCreate : public QWidget { // Создание нового юзера

};

class TUserEdit : public QWidget { // Редактирование юзера

};

class TUserDelete : public QWidget { // Удаление юзера

};


#endif //THEATRE_ADMIN_TUSER_H
