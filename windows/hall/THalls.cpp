#include <utils/TDB.h>
#include "THalls.h"
#include "THallPreview.h"

THalls::THalls() {
	// Fill scroll with widgets
	QJsonArray halls = TDB().request("t_halls", {{"preview", "true"}}).toArray();

	for (QJsonValue v : halls)
		layout->addWidget(new THallPreview(v.toObject()));
}
