#ifndef TARTICLE_H
#define TARTICLE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <utils/TCheckBox.h>
#include <QtCore/QJsonObject>
#include <QtWidgets/QtWidgets>
#include <utils/TDB.h>

class TArticle : public QWidget {
Q_OBJECT
public:
	TArticle(QJsonObject o);

	void edt();

	void save();

	void del();

	QLineEdit *title;
	QTextEdit *desc;
	QPushButton *b_edt;
	QPushButton *b_del;
	int id;
};

#endif // TARTICLE_H
