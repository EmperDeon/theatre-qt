#ifndef THEATRE_ADMIN_TPERF_H
#define THEATRE_ADMIN_TPERF_H
#include <utils/TComboBox.h>
#include <templates/TTModel.h>

class TPerf : public TTModel {
	QLineEdit *l_name, *l_auth, *l_type;
	QTextEdit *e_desc_s;

public:
	TPerf(QJsonObject o);

	virtual QString getPath() override;

	virtual void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_TPERF_H
