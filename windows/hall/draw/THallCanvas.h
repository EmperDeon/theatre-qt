#ifndef THEATRE_ADMIN_THALLCANVAS_H
#define THEATRE_ADMIN_THALLCANVAS_H
#define GET_C(c) QColor(c, c, c)

#include <QtWidgets/QtWidgets>
#include <windows/hall/THall.h>

class THall;

class THallCanvas : public QWidget {
	int w = 100, h = 100;
	int cw = 15, ch = 15;
	THall *wnd;
	int *map;

	// Mouse-related
	int r_start_x = -1, r_start_y = -1;

public:
	THallCanvas(THall *wn);

	void setSize(int w, int h);

	void crop();

protected:
	void paintEvent(QPaintEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;

	void swapIf(int &i1, int &i2);
};

#endif //THEATRE_ADMIN_THALLCANVAS_H
