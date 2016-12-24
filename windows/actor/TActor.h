#ifndef ACTOR_H
#define ACTOR_H

#include <QtWidgets/QtWidgets>


class TActor : public QWidget {
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

	TActor(QJsonObject o);

public slots:

};

#endif // ACTORS_H
