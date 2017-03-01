#ifndef THEATRE_ADMIN_TPERFAPPROVE_H
#define THEATRE_ADMIN_TPERFAPPROVE_H

#include <QtWidgets>
#include <templates/TTModels.h>
#include <utils/TComboBox.h>


class TPerfApprove : public TTModels {
public:
	TPerfApprove();
};

class TPerfApproveW : public QFrame {
	int id, t_id;
	QPushButton *b_edt;
	QLineEdit *e_author, *e_name;
	TComboBox *e_type;

public:
	TPerfApproveW(QJsonObject o);

	void approve();

	void remove();

	void edit();

	void send(int a);
};


#endif //THEATRE_ADMIN_TPERFAPPROVE_H
