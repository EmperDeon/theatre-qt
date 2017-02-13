#ifndef THEATRE_ADMIN_THALLCREATE_H
#define THEATRE_ADMIN_THALLCREATE_H

#include <QtWidgets>
#include "THall.h"

class THallCreate : public QWidget {
	THall *hall;

	QLineEdit *l_h_w, *l_h_h;

public:
	THallCreate();

	void save();

	void reset();

	void setSize();

};


#endif //THEATRE_ADMIN_THALLCREATE_H
