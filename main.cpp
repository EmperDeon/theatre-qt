#include <windows/TMainWindow.h>
#include <QApplication>
#include <QtCore/QFile>


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
