#include "TArticles.h"
#include <utils/TDB.h>
#include <windows/article/TArticle.h>


TArticles::TArticles() : TTModel() {
	// Fill scroll with widgets
	QJsonArray users = TDB().request("articles").toArray();

	for (QJsonValue v : users)
		layout->addWidget(new TArticle(v.toObject()));
}
