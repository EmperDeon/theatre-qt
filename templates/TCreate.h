#ifndef THEATRE_ADMIN_TCREATE_H
#define THEATRE_ADMIN_TCREATE_H
#include <QtWidgets/QtWidgets>

class TCreate : public QWidget {
	QPushButton *b_create, *b_reset;

protected:
	QFormLayout *layout;

public:
	TCreate();

	void create();

	virtual void reset() {};

	virtual QString getPath() = 0;

	virtual QMap<QString, QString> getParams() = 0;
};


#endif //THEATRE_ADMIN_TCREATE_H
