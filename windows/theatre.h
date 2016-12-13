#ifndef THEATRE_H
#define THEATRE_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtCore/QJsonObject>

class theatre : public QWidget {
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

	QPushButton *edit;
	QPushButton *del;

	QHBoxLayout *l;
	QVBoxLayout *l1;
	QVBoxLayout *l2;

	theatre(QJsonObject o);

	void CEdit();


public slots:


};

#endif // THEATRE_H
