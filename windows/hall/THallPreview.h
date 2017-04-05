#ifndef THEATRE_ADMIN_THALLPREVIEW_H
#define THEATRE_ADMIN_THALLPREVIEW_H

#include <QtWidgets/QtWidgets>

class THallPreview : public QFrame {
	int id;

public:
	THallPreview(QJsonObject o);

	void edt();

	void del();

	QString getPath();
};


#endif //THEATRE_ADMIN_THALLPREVIEW_H
