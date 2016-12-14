#ifndef ACTORS_H
#define ACTORS_H


#include <QtWidgets/QLabel>
#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <templates/TTModel.h>
#include "windows/actor.h"

class TTModel;

class actors : public TTModel {
Q_OBJECT
public:
	QPushButton *add;
	actor *test;
	QVBoxLayout *l;

	actors();

public slots:

};

#endif // ACTORS_H
