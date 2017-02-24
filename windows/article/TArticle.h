#ifndef THEATRE_ADMIN_TARTICLE_H
#define THEATRE_ADMIN_TARTICLE_H

#include <QtWidgets/QtWidgets>
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

#endif // THEATRE_ADMIN_TARTICLE_H
