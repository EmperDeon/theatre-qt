#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>

#ifndef THEATRE_ADMIN_edit1theatre_H
#define THEATRE_ADMIN_edit1theatre_H


class edit_theatre : public QWidget {
Q_OBJECT
public:
	QComboBox *name;

	QLineEdit *e_name;
	QLineEdit *address;
	QLineEdit *tel_num;
	QTextEdit *desc;

	QLabel *l_name;
	QLabel *l_e_name;
	QLabel *l_address;
	QLabel *l_tel_num;
	QLabel *l_desc;

	QPushButton *entr;
	QPushButton *cancel;

	QVBoxLayout *l;
	QHBoxLayout *lh;

	edit_theatre();


public slots:

};


#endif //THEATRE_ADMIN_TBOOKING_H
