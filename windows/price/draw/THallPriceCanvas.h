#ifndef THEATRE_ADMIN_TPRICECANVAS_H
#define THEATRE_ADMIN_TPRICECANVAS_H
#define GET_C(c) QColor(c, c, c)

#include <QtWidgets/QtWidgets>
#include <windows/price/draw/THallPrice.h>

class THallPrice;

class THallPriceCanvas : public QWidget {
	int w = 150, h = 80;
	int cs = 20;
	int off_x = 0, off_y = 0, mw = 0, mh = 0;

	int *seat_s = nullptr, *sect_s = nullptr, *seat_t = nullptr, *seat_r = nullptr, *price_s = nullptr;
	QList<TPriceSeat> seat_n;
	QList<TPriceCoord> sect_n;

	THallPrice *wnd;
	QScrollBar *scroll_w, *scroll_h;

	// Mouse-related
	int r_start_x = -1, r_start_y = -1, lastFill = 2;

public:
	THallPriceCanvas(THallPrice *wn, QScrollBar *s_w, QScrollBar *s_h);

	void moveView(int x, int y);

	QJsonObject toJson();

	void fromJson(QJsonObject o);

	void loadHall(QJsonObject o);

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

	QPair<int, TPriceSeat> getSeatAt(int cx, int cy);
};

#endif //THEATRE_ADMIN_TPRICECANVAS_H
