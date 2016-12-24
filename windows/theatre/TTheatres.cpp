#include "TTheatres.h"
#include <utils/TDB.h>
#include <windows/theatre/TTheatre.h>

TTheatres::TTheatres() {
	// Fill scroll with widgets
	QJsonArray users = TDB().request("theatres").toArray();

	for (QJsonValue v : users)
		layout->addWidget(new TTheatre(v.toObject()));
}
