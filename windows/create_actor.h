#ifndef THEATRE_ADMIN_create_actor_H
#define THEATRE_ADMIN_create_actor_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineedit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>

class create_actor : public QWidget {
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
	create_actor();
};

#endif // CREATE_ACTOR_H
