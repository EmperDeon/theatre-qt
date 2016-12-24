#include "TPosters.h"
#include <utils/TDB.h>
#include "TPoster.h"

TPosters::TPosters() {
	QJsonArray arr = TDB().request("posters").toArray();

	for (QJsonValue v : arr) {
		layout->addWidget(new TPoster(v.toObject()));
	}
}
