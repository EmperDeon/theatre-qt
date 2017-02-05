#ifndef TARTICLE_H
#define TARTICLE_H
#include <utils/TCheckBox.h>
#include <utils/TDB.h>
#include <templates/TTModel.h>

class TArticle : public TTModel {
	QLineEdit *title;
	QTextEdit *desc;

public:
	TArticle(QJsonObject o);

	virtual QString getPath() override;

	virtual void setFEnabled(bool b) override;

	QMap<QString, QString> getParams() override;

};
#endif // TARTICLE_H
