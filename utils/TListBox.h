#ifndef THEATRE_ADMIN_TLISTBOX_H
#define THEATRE_ADMIN_TLISTBOX_H

#include <QtWidgets/QListWidget>

class TListBox;

class TListBox : public QListWidget {
	QMap<QString, int> map;
	QList<int> selected;

public:
	TListBox(QString t);

	QList<int> getIds() { return selected; }

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};


#endif //THEATRE_ADMIN_TLISTBOX_H
