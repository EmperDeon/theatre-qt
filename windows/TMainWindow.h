#ifndef THEATRE_ADMIN_MAINWINDOW_H
#define THEATRE_ADMIN_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "TMainMenu.h"
#include <QDebug>

class TMainMenu;

class TMainWindow : public QMainWindow {
	TMainMenu *w_menu;
	QHBoxLayout *l;
	QWidget *w_curr = nullptr;
	bool loadingWidget = false;

	// StatusBar permanent label
	QLabel *l_status;

	QWidget *getNewMainWidget();

	QWidget *getNewLoadWidget();

public:
	TMainWindow();

	void changeCurrent(QString s);

	void showStatusMessage(QString s);

	// Singleton function for TDB
	static TMainWindow *getInstance() {
		static TMainWindow *instance = nullptr;

		if (!instance) {
			instance = new TMainWindow;
		}

		return instance;
	}
};


#endif //THEATRE_ADMIN_MAINWINDOW_H
