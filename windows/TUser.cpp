#include <utils/TDB.h>
#include <utils/TListBox.h>
#include "TUser.h"


// TUsers
TUsers::TUsers() {
	QVBoxLayout *l = new QVBoxLayout;

	l->addWidget(new TUser(QJsonObject()));

	setLayout(l);
}
// TUsers



// TUser
TUser::TUser(QJsonObject o) {
	QVBoxLayout *l = new QVBoxLayout;

	c = new TListBox("u__perms");

	l->addWidget(c);

	setLayout(l);

}
// TUser


