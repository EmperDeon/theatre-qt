#ifndef THEATRE_ADMIN_THALL_H
#define THEATRE_ADMIN_THALL_H
#define GET_C(c) QColor(c, c, c)

#include <QtWidgets/QtWidgets>

class THall : public QWidget {
	int w = 100, h = 100;
	int cw = 15, ch = 15;

	int *map;

	// Mouse-related
	int r_start_x = -1, r_start_y = -1;

public:
	THall();

	void setSize(int w, int h);

	void crop();

protected:
	void paintEvent(QPaintEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;

	void swapIf(int &i1, int &i2);
};


#endif //THEATRE_ADMIN_THALL_H
