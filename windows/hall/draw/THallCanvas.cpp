#include "THallCanvas.h"

void THallCanvas::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, false);

	// Grid
	p.setPen(Qt::NoPen);
	p.setBrush(QBrush(GET_C(223))); // 235

	p.drawRect(0, 0, w * cw - 1, h * ch - 1);
	p.setPen(QPen(Qt::white));

	for (int x = 1; x < w; x++)
		p.drawLine(x * cw, 1, x * cw, h * ch - 2);

	for (int y = 1; y < h; y++)
		p.drawLine(1, y * ch, w * cw - 2, y * cw);

	// Areas
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++) {
			if (map[x * w + y]) {
				p.setBrush(QBrush(QColor(170, 170, 255)));
				p.drawRect(x * cw, y * ch, cw, ch);

			}
		}

	// Draw border around
	p.setPen(GET_C(172));
	p.setBrush(Qt::NoBrush); // 235

	p.drawRect(0, 0, width() - 1, height() - 1);

	p.end();
	event->accept();
}

THallCanvas::THallCanvas(THall *wn) : wnd(wn) {
	map = new int[w * h];
	for (int i = 0; i < w * h; i++)
		map[i] = 0;

}

void THallCanvas::mousePressEvent(QMouseEvent *event) {
//	if (event->modifiers() == Qt::ShiftModifier) {
	r_start_x = (event->x() / cw);
	r_start_y = (event->y() / ch);
//	}

	mouseMoveEvent(event);
}

void THallCanvas::mouseMoveEvent(QMouseEvent *event) {
	int fill = event->buttons() == Qt::LeftButton ? 1 : 0;
	int start_x = event->modifiers() == Qt::ShiftModifier ? r_start_x : (event->x() / cw);
	int start_y = event->modifiers() == Qt::ShiftModifier ? r_start_y : (event->y() / ch);
	int end_x = (event->x() / cw) + 1;
	int end_y = (event->y() / ch) + 1;

	if (end_x <= start_x) {
		start_x++;
		end_x--;
	}

	if (end_y <= start_y) {
		start_y++;
		end_y--;
	}

	swapIf(start_x, end_x);
	swapIf(start_y, end_y);

	start_x = start_x < 0 ? 0 : start_x;
	start_y = start_y < 0 ? 0 : start_y;

	for (int x = start_x; x < end_x; x++)
		for (int y = start_y; y < end_y; y++) {
			map[x * w + y] = fill;
		}


	update();
}

void THallCanvas::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event)

	r_start_x = -1;
	r_start_y = -1;
}

void THallCanvas::setSize(int w, int h) {
	int *nmap = new int[w * h], *omap = map;
	int ow = this->w, oh = this->h;
	qDebug() << w << h << ow << oh;

	// Clear new map
	for (int i = 0; i < w * h; i++)
		nmap[i] = 0;

	// Fill with old data
	for (int x = 0; x < qMin(ow, w); x++)
		for (int y = 0; y < qMin(oh, h); y++) {
			nmap[x * w + y] = omap[x * ow + y];
		}

	this->w = w;
	this->h = h;
	this->map = nmap;
	delete omap;

	update();
}

void THallCanvas::crop() {

}

void THallCanvas::swapIf(int &i1, int &i2) {
	int t = qMin(i1, i2);
	i2 = qMax(i1, i2);
	i1 = t;
}