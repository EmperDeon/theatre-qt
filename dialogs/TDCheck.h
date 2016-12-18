#ifndef THEATRE_ADMIN_TDCHECK_H
#define THEATRE_ADMIN_TDCHECK_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QCheckBox>
#include <QtCore/QMap>


class TDCheck : QDialog {
	QList<QCheckBox *> lst;
	QMap<QString, QString> map;

public:
	TDCheck(QMap<QString, QString> m, QStringList s);

	QStringList getSelected();

	static QStringList getSelection(QMap<QString, QString> m, QStringList s);
};


#endif //THEATRE_ADMIN_TDCHECK_H
