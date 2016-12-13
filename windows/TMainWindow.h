#ifndef THEATRE_ADMIN_MAINWINDOW_H
#define THEATRE_ADMIN_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "TMainMenu.h"

class TMainMenu;

class TMainWindow : public QMainWindow {
	TMainMenu *w_menu;
	QHBoxLayout *l;
	QWidget *w_curr = nullptr;
	QString s_curr;

	QWidget *getNewMainWidget();

public:
	TMainWindow();

	void changeCurrent(QString s);
};


#endif //THEATRE_ADMIN_MAINWINDOW_H
