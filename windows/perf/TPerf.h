#ifndef THEATRE_ADMIN_TPERF_H
#define THEATRE_ADMIN_TPERF_H

#include <QtWidgets/QtWidgets>
#include <QtCore/QJsonObject>
#include <utils/TComboBox.h>

class TPerf : public QWidget {
	QPushButton *b_edt;
	QPushButton *b_del;
	int id;

	QLineEdit *l_name, *l_auth, *l_type;
	QTextEdit *e_desc_s;

public:
	TPerf(QJsonObject o);

	void edt();

	void save();

	void del();
};


#endif //THEATRE_ADMIN_TPERF_H
