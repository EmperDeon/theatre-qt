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

QJsonArray TUsers::getPerms() {
	return TConfig::get("lastPerms").toArray();
}

bool TUsers::hasPerm(QString k) {
	return getPerms().contains(k);
}
// TUsers