include<QtWidgets / QLabel>

#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>

#ifndef THEATRE_ADMIN_TBOOKING_H
#define THEATRE_ADMIN_TBOOKING_H


class create1theatre : public QWidget {
Q_OBJECT
public:
	QLineEdit *name;
	QLineEdit *address;
	QLineEdit *tel_num;
	QTextEdit *desc;

	QLabel *l_name;
	QLabel *l_address;
	QLabel *l_tel_num;
	QLabel *l_desc;

	QPushButton *entr;
	QPushButton *cancel;

	QVBoxLayout *l;
	QHBoxLayout *lh;

	create1theatre();


public slots:

};


#endif //THEATRE_ADMIN_TBOOKING_H
