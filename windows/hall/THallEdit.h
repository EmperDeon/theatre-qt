#ifndef THEATRE_ADMIN_THALLEDIT_H
#define THEATRE_ADMIN_THALLEDIT_H

#include <QtWidgets>
#include <templates/TCreate.h>
#include <utils/TComboBox.h>
#include <windows/hall/draw/THall.h>

class THallEdit : public QWidget {
	int id;
	QJsonObject obj;
	TComboBox *c_box;

	THall *hall;

	QLineEdit *l_h_w, *l_h_h, *l_h_n;

public:
	THallEdit();

	QString getPath();

	QMap<QString, QString> getParams();

	void changeIndex(int i);

	void reset();

	void save();

	void setSize();
};


#endif //THEATRE_ADMIN_THALLEDIT_H
