#ifndef TARTICLECREATE_H
#define TARTICLECREATE_H

#include <QtWidgets/QtWidgets>
#include <QtWidgets/QtWidgets>
#include <utils/TCheckBox.h>
#include <templates/TCreate.h>

class TArticleCreate : public TCreate {
	QLineEdit *name;
	QTextEdit *desc_s, *desc;
public:
	TArticleCreate();

	virtual void create();

	virtual void reset();

};


#endif // TARTICLECREATE_H
