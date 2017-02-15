#ifndef THEATRE_ADMIN_TPERFEDIT_H
#define THEATRE_ADMIN_TPERFEDIT_H


#include <QtWidgets/QtWidgets>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>
#include <templates/TEdit.h>
#include <utils/TFileUpload.h>

class TPerfEdit : public TEdit {
	// Global perfs
	TComboBox *p_type;
	QLineEdit *p_name, *p_auth;
	QPushButton *p_add;
	QWidget *p_wgt;

	TComboBox *p_box;

	TComboBox *e_hall;
	QTextEdit *e_desc, *e_desc_s;
	TFileUpload *e_img;

public:
	TPerfEdit();

	void add();

	virtual void reset();

	virtual QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_TPERFEDIT_H
