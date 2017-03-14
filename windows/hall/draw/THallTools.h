#ifndef THEATRE_ADMIN_THALLTOOLS_H
#define THEATRE_ADMIN_THALLTOOLS_H
#include <QtWidgets/QtWidgets>


class THallTools : public QWidget {
	QButtonGroup *bg;

public:
	THallTools();

	int getCurrentId();

	void setCurrentId(int i);
};


#endif //THEATRE_ADMIN_THALLTOOLS_H
