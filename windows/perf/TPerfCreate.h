#ifndef THEATRE_ADMIN_TPERFCREATE_H
#define THEATRE_ADMIN_TPERFCREATE_H

#include <QtWidgets/QtWidgets>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>
#include <utils/TFileUpload.h>
#include <utils/TCheckBox.h>

class TPerfCreate : public TCreate {
	// Global perfs
	TComboBox *p_type;
	QLineEdit *p_name, *p_auth;
	QPushButton *p_add;
	QWidget *p_wgt;

	TComboBox *p_box;

	TComboBox *e_hall;
	QTextEdit *e_desc, *e_desc_s;
	TFileUpload *e_img;

	TCheckBox *e_actors;

public:
	TPerfCreate();

	void add();

	virtual void reset() override;

	QString getPath() override;

	QMap<QString, QString> getParams() override;
};


#endif //THEATRE_ADMIN_TPERFCREATE_H
