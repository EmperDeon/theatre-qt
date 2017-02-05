#ifndef TARTICLECREATE_H
#define TARTICLECREATE_H
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>

class TArticleCreate : public TCreate {
	QLineEdit *name;
	QTextEdit *desc_s, *desc;


public:
	TArticleCreate();

	virtual void reset();

	QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif // TARTICLECREATE_H
