#ifndef THEATRES_H
#define THEATRES_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <Windows/theatre.h>


class theatres : public QWidget {
Q_OBJECT
public:
	QPushButton *add;
	theatre *test;
	QVBoxLayout *l;

	theatres();

public slots:

};


#endif // THEATRES_H
