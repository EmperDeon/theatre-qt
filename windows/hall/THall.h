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


public:
	THall();

	void setSize(int w, int h);

	void crop();


};


#endif //THEATRE_ADMIN_THALL_H
