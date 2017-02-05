#ifndef ACTORS_H
#define ACTORS_H

#include <QtWidgets/QtWidgets>
#include <templates/TTModels.h>
#include "TActor.h"


class TTModels;

class TActors : public TTModels {
Q_OBJECT
public:
	QPushButton *add;
	TActor *test;
	QVBoxLayout *l;

	TActors();

public slots:

};

#endif // ACTORS_H
