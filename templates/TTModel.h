#ifndef THEATRE_ADMIN_TTMODEL_H
#define THEATRE_ADMIN_TTMODEL_H

#include <QtCore/QJsonObject>
#include <QtWidgets/QtWidgets>

class TTModel : public QFrame {
	QPushButton *b_edt, *b_del;
	QLabel *l_upd;

protected:
	int id;
	QHBoxLayout *l;
	QFormLayout *layout;

public:
	TTModel(QJsonObject o);

	void edt();

	void del();

	void save();

	virtual QString getPath() = 0;

	virtual void setFEnabled(bool b) = 0;

	virtual QMap<QString, QString> getParams() = 0;
};


#endif //THEATRE_ADMIN_TTMODEL_H
