#ifndef THEATRE_ADMIN_TARTICLECREATE_H
#define THEATRE_ADMIN_TARTICLECREATE_H
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>
#include <utils/TFileUpload.h>

class TArticleCreate : public TCreate {
	QLineEdit *name;
	QTextEdit *desc_s, *desc;
	TFileUpload *img;

public:
	TArticleCreate();

	virtual void reset();

	QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif // THEATRE_ADMIN_TARTICLECREATE_H
