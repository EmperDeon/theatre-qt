#ifndef THEATRE_ADMIN_TDCHECK_H
#define THEATRE_ADMIN_TDCHECK_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QCheckBox>
#include <QtCore/QMap>


class TDCheck : QDialog {
	QList<QCheckBox *> lst;
	QMap<QString, int> map;

public:
	TDCheck(QMap<QString, int> m, QList<int> s);

	QList<int> getSelected();

	static QList<int> getSelection(QMap<QString, int> m, QList<int> s);
};


#endif //THEATRE_ADMIN_TDCHECK_H
