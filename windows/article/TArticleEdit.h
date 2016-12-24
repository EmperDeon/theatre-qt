#ifndef TARTICLEEDIT_H
#define TARTICLEEDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TEdit.h>

class TArticleEdit : public TEdit {
	QTextEdit *desc, *desc_s;
	QLineEdit *name;
	TCheckBox *l_perms;

public:
	TArticleEdit();

	virtual void submit();

	virtual void reset();

	virtual void load();
};


#endif // TARTICLEEDIT_H
