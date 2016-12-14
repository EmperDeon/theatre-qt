#include "TUsers.h"
#include <utils/TDB.h>
#include <windows/user/TUser.h>

// TUsers
TUsers::TUsers() : TTModel() {

	// Fill scroll with widgets
	QJsonArray users = TDB().request("users").toArray();

	for (auto v : users)
		layout->addWidget(new TUser(v.toObject()));

}
// TUsers