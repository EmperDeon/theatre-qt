#ifndef THEATRE_ADMIN_TCHECKBOX_H
#define THEATRE_ADMIN_TCHECKBOX_H

#include <QtWidgets/QListWidget>
#include <QtCore/QtCore>

class TCheckBox;

class TCheckBox : public QListWidget {
	QMap<QString, QString> map;
	QStringList selected;

public:
	TCheckBox(QString t);

	void clearList() { selected.clear(); }

	void setIds(QJsonArray l);

	void setIds(QStringList l);

	QString getIds();

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};


#endif //THEATRE_ADMIN_TCHECKBOX_H
