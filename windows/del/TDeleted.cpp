#include <utils/TDB.h>
#include "TDeleted.h"
#include "TDeletedTab.h"

TDeleted::TDeleted() {
	o_del = TDB().request("utils/deleted").toArray();

	for (QJsonValue v : o_del) {
		QJsonObject o = v.toObject();

		TDeletedTab *n = new TDeletedTab(o["path"].toString(), o["arr"].toArray());
		this->addTab(n, o["name"].toString());
	}
}
