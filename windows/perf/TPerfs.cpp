#include <utils/TDB.h>
#include "TPerfs.h"
#include "TPerf.h"

TPerfs::TPerfs() {
	QJsonArray arr = TDB().request("t_perfs").toArray();

	for (QJsonValue v : arr) {
		layout->addWidget(new TPerf(v.toObject()));
	}
}
