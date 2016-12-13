#ifndef THEATRE_ADMIN_TMAINMENU_H
#define THEATRE_ADMIN_TMAINMENU_H

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsOpacityEffect>
#include "TMainWindow.h"

class TMainWindow;

class TMainMenu : public QWidget {
Q_OBJECT
	TMainWindow *wnd;
	QJsonArray menuStructure;

	QVBoxLayout *l_main, *l_menu;
	QScrollArea *menu_s;
	QPushButton *b_hide;


	// Animation
	QGraphicsOpacityEffect *e_menu;

public slots:

	void entryClick(QString name);


public:
	TMainMenu(TMainWindow *w);

	void hideMenu();

	void reformMenu();

	void createStructure();

	QLabel *getNewMenuLabel(QJsonObject o, bool sub) const;
};


#endif //THEATRE_ADMIN_TMAINMENU_H
