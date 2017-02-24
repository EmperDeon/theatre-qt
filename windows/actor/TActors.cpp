#include "TActors.h"
#include "TActor.h"
#include <utils/TDB.h>


TActors::TActors() {
	QJsonArray a = TDB().request("actors").toArray();

	for (QJsonValue v : a) {
		QWidget *n = new TActor(v.toObject());
		layout->addWidget(n);
	}
}
