#ifndef THEATRE_ADMIN_TLISTBOX_H
#define THEATRE_ADMIN_TLISTBOX_H

#include <QtWidgets/QListWidget>

class TListBox;

class TListBox : public QListWidget {
	QMap<QString, QString> map;
	QStringList selected;

public:
	TListBox(QString t);

	void clearList() { selected.clear(); }

	void setIds(QStringList l);

	QStringList getIds() { return selected; }

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};


#endif //THEATRE_ADMIN_TLISTBOX_H
