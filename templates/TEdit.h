#ifndef THEATRE_ADMIN_TEDIT_H
#define THEATRE_ADMIN_TEDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TComboBox.h>


class TEdit : public QWidget {
Q_OBJECT

	QPushButton *b_create, *b_reset;

protected:
	int id;
	QJsonObject obj;
	TComboBox *c_box;
	QFormLayout *layout;

public:
	TEdit();

	virtual void submit() {};

	virtual void reset() {};

	virtual void load() {};

public slots:

	void changeIndex(int i);
};


#endif //THEATRE_ADMIN_TEDIT_H
