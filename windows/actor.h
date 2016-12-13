#ifndef ACTOR_H
#define ACTOR_H


#include <QtWidgets/QLabel>
#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtCore>

class actor : public QWidget {
Q_OBJECT
public:
	QLineEdit *name;
	QTextEdit *bio;

	QLabel *l_name;
	QLabel *l_bio;

	QPushButton *edit;
	QPushButton *del;

	QHBoxLayout *l;
	QVBoxLayout *l1;
	QVBoxLayout *l2;

	actor(QJsonObject o);

public slots:

};

#endif // ACTORS_H
