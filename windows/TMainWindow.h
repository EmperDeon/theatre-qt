#ifndef THEATRE_ADMIN_MAINWINDOW_H
#define THEATRE_ADMIN_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "TMainMenu.h"

class TMainMenu;

class TMainWindow : public QMainWindow {
	TMainMenu *w_menu;
	QHBoxLayout *l;
	QWidget *w_curr = nullptr;
	bool loadingWidget = false;

	QWidget *getNewMainWidget();

	QWidget *getNewLoadWidget();

public:
	TMainWindow();

	void changeCurrent(QString s);
};


#endif //THEATRE_ADMIN_MAINWINDOW_H
