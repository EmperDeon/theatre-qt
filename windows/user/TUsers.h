#ifndef THEATRE_ADMIN_TUSERS_H
#define THEATRE_ADMIN_TUSERS_H
#include <QtWidgets>
#include <templates/TTModels.h>

class TTModels;

class TUsers : public TTModels { // Отображение всех юзеров

public:
	TUsers();

	static QJsonArray getPerms();

	static bool hasPerm(QString k);
};


#endif //THEATRE_ADMIN_TUSERS_H
