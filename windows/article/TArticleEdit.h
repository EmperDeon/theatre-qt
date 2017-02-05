#ifndef TARTICLEEDIT_H
#define TARTICLEEDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>

class TArticleEdit : public TEdit {
	QTextEdit *desc, *desc_s;
	QLineEdit *name;

public:
	TArticleEdit();

	virtual void reset();

	virtual QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif // TARTICLEEDIT_H
