#ifndef THEATRE_ADMIN_TEDIT_H
#define THEATRE_ADMIN_TEDIT_H

#include <QtWidgets/QtWidgets>
#include <utils/TComboBox.h>


class TEdit : public QWidget {
	QPushButton *b_create, *b_reset;

protected:
	int id;
	QJsonObject obj;
	TComboBox *c_box;
	QFormLayout *layout;

	void changeIndex(int i);

public:
	TEdit();

	void submit();

	virtual void reset() {};

	void load();

	virtual QString getPath() { return ""; };

	virtual QMap<QString, QString> getParams() = 0;

};


#endif //THEATRE_ADMIN_TEDIT_H
