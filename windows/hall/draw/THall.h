#ifndef THEATRE_ADMIN_THALL_H
#define THEATRE_ADMIN_THALL_H
#define GET_C(c) QColor(c, c, c)

#include <QtWidgets/QtWidgets>
#include <windows/hall/draw/THallCanvas.h>
#include <windows/hall/draw/THallTools.h>

class THallCanvas;

class THallTools;

class THall : public QWidget {
	THallCanvas *w_canvas;
	THallTools *w_tools;

	QScrollBar *s_w, *s_h;

public:
	THall();

	void setSize(int w, int h);

	void crop();

	int getCurrentTool();

	void setCurrentTool(int i);

	void load();

	void save();

	void changeScale(int mw, int mh);

	void setScroll(int x, int y);

protected:
	void keyReleaseEvent(QKeyEvent *event) override;
};


#endif //THEATRE_ADMIN_THALL_H
