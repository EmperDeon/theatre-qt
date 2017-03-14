#ifndef THEATRE_ADMIN_THALLCANVAS_H
#define THEATRE_ADMIN_THALLCANVAS_H
#define GET_C(c) QColor(c, c, c)

#include <QtWidgets/QtWidgets>
#include <windows/hall/draw/THall.h>

class THall;

class THallCanvas : public QWidget {
	int w = 150, h = 80;
	int cs = 20;
	int ox = 0, oy = 0, mw = 0, mh = 0;

	THall *wnd;
	int *map;

	// Mouse-related
	int r_start_x = -1, r_start_y = -1, lastFill = 2;

public:
	THallCanvas(THall *wn);

	void setSize(int w, int h);

	void crop();

	void moveView(int x, int y);

	QJsonObject toJson();

	void fromJson(QJsonObject o);

	void scrollW(int p);

	void scrollH(int p);

protected:
	void paintEvent(QPaintEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;

	void wheelEvent(QWheelEvent *event) override;

	void swapIf(int &i1, int &i2);

	int getCell(int x, int y) const;

	void setCell(int x, int y, int f);
};

#endif //THEATRE_ADMIN_THALLCANVAS_H
