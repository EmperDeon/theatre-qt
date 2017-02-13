#ifndef THEATRE_ADMIN_THALLPREVIEW_H
#define THEATRE_ADMIN_THALLPREVIEW_H

#include <templates/TTModel.h>

class THallPreview : public TTModel {


public:
	THallPreview(QJsonObject o);

	QString getPath() override;

	void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_THALLPREVIEW_H
