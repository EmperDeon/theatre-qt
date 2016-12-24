#ifndef THEATRE_ADMIN_TPERFCREATE_H
#define THEATRE_ADMIN_TPERFCREATE_H

#include <QtWidgets/QtWidgets>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>

class TPerfCreate : public TCreate {
	// Global perfs
	TComboBox *p_type;
	QLineEdit *p_name, *p_auth;
	QPushButton *p_add;
	QWidget *p_wgt;

	TComboBox *p_box;

	QTextEdit *e_desc, *e_desc_s;

public:
	TPerfCreate();

	void add();

	virtual void create() override;

	virtual void reset() override;
};


#endif //THEATRE_ADMIN_TPERFCREATE_H
