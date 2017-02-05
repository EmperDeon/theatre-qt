#include "TUsers.h"
#include <utils/TDB.h>
#include <windows/user/TUser.h>

// TUsers
TUsers::TUsers() : TTModels() {
	// Fill scroll with widgets
	QJsonArray users = TDB().request("u_apis").toArray();

	for (QJsonValue v : users)
		layout->addWidget(new TUser(v.toObject()));

}
// TUsers