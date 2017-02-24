#ifndef THEATRE_ADMIN_TARTICLEEDIT_H
#define THEATRE_ADMIN_TARTICLEEDIT_H
#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>
#include <utils/TFileUpload.h>

class TArticleEdit : public TEdit {
	QTextEdit *desc, *desc_s;
	QLineEdit *name;
	TFileUpload *img;

public:
	TArticleEdit();

	virtual void reset();

	virtual QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif // THEATRE_ADMIN_TARTICLEEDIT_H
