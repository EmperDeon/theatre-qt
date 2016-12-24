#ifndef THEATRE_ADMIN_TCHECKBOX_H
#define THEATRE_ADMIN_TCHECKBOX_H

#include <QtWidgets/QListWidget>

class TCheckBox;

class TCheckBox : public QListWidget {
	QMap<QString, QString> map;
	QStringList selected;

public:
	TCheckBox(QString t);

	void clearList() { selected.clear(); }

	void setIds(QStringList l);

	QStringList getIds() { return selected; }

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};


#endif //THEATRE_ADMIN_TCHECKBOX_H
