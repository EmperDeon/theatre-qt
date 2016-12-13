
#include <dialogs/TDLogin.h>
#include <QApplication>
#include <windows/TMainWindow.h>
#include <QtCore/QFile>
#include <utils/TDB.h>
#include <QtCore>
#include "windows/actors.h"

class QApplication;

class TMainWindow;

QString readStyleSheet() {
	QFile f(":/qss.qss");
	f.open(QFile::ReadOnly);
	return QString::fromUtf8(f.readAll());
}

int main(int argc, char **argv) {
	QApplication a(argc, argv);

	a.setStyleSheet(readStyleSheet());

	TMainWindow *w = new TMainWindow;
	w->show();


	return a.exec();
}
