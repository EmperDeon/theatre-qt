#ifndef THEATRE_ADMIN_create_actor_H
#define THEATRE_ADMIN_create_actor_H

#include <QtWidgets/QtWidgets>


class TActorCreate : public QWidget {
Q_OBJECT
public:
	QLineEdit *name;
	QTextEdit *bio;

	QLabel *l_name;
	QLabel *l_bio;

	QPushButton *entr;
	QPushButton *cancel;

	QVBoxLayout *l;
	QHBoxLayout *lh;
public:
	TActorCreate();
};

#endif // CREATE_ACTOR_H
