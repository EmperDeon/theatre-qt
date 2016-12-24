#ifndef THEATRE_H
#define THEATRE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <utils/TCheckBox.h>
#include <QtCore/QJsonObject>
#include <QtWidgets/QtWidgets>
#include <utils/TDB.h>

class TTheatre : public QWidget {
Q_OBJECT
public:
	TTheatre(QJsonObject o);

	void edt();

	void save();

	void del();

	QLineEdit *name;
	QLineEdit *address;
	QLineEdit *phone;
	QTextEdit *desc;
	QPushButton *b_edt;
	QPushButton *b_del;
	int id;
};


#endif // THEATRE_H
