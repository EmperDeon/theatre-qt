#ifndef ACTORS_H
#define ACTORS_H

#include <QtWidgets/QtWidgets>
#include <templates/TTModels.h>
#include "TActor.h"


class TTModel;

class TActors : public TTModel {
Q_OBJECT
public:
	QPushButton *add;
	TActor *test;
	QVBoxLayout *l;

	TActors();

public slots:

};

#endif // ACTORS_H
