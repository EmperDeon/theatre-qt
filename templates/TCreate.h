#ifndef THEATRE_ADMIN_TCREATE_H
#define THEATRE_ADMIN_TCREATE_H

#include <QtWidgets/QtWidgets>

class TCreate : public QWidget {
	QPushButton *b_create, *b_reset;

protected:
	QFormLayout *layout;

public:
	TCreate();

	virtual void create() {};

	virtual void reset() {};

};


#endif //THEATRE_ADMIN_TCREATE_H
