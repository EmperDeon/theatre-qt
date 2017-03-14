#include "THallCanvas.h"

void THallCanvas::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, false);

	// Offset
	mw = (w * cs) - size().width() + 200;
	mh = (h * cs) - size().height() + 200;

	ox = ox > mw ? mw : ox;
	oy = oy > mh ? mh : oy;

	ox = ox < 0 ? 0 : ox;
	oy = oy < 0 ? 0 : oy;
	// Offset


	// Grid
	p.setPen(Qt::NoPen);
	p.setBrush(QBrush(GET_C(233))); // 235

	p.drawRect(0, 0, width(), height());
	p.setPen(QPen(GET_C(243)));

	p.translate(-ox, -oy);

	for (int x = 1; x <= w; x++)
		p.drawLine(x * cs, 1, x * cs, h * cs - 2);

	for (int y = 1; y <= h; y++)
		p.drawLine(1, y * cs, w * cs - 2, y * cs);

	// Areas
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++) {
			int i = getCell(x, y);
			if (i == 1) {
				p.setBrush(QBrush(QColor(170, 170, 255)));

			} else if (i == 2 || i == 3) {
				p.setBrush(QBrush(GET_C(150)));

			} else {
				p.setBrush(QBrush(GET_C(223)));

			}

			p.drawRect(x * cs, y * cs, cs, cs);
		}

	p.translate(0, 0);

	// Draw border around
	p.setPen(GET_C(172));
	p.setBrush(Qt::NoBrush); // 235

	p.drawRect(ox, oy, ox + width() - 1, oy + height() - 1);
	p.end();
	event->accept();
}

int THallCanvas::getCell(int x, int y) const {
	if (x < w && y < h) {
		int i = map[x + y * w];

		return i;
	} else
		return 0;
}

void THallCanvas::setCell(int x, int y, int f) {
	if (x < w && y < h)
		map[x + y * w] = f;
}

THallCanvas::THallCanvas(THall *wn) : wnd(wn) {


}

void THallCanvas::mousePressEvent(QMouseEvent *event) {
	r_start_x = ((event->x() + ox) / cs);
	r_start_y = ((event->y() + oy) / cs);

	mouseMoveEvent(event);
}

void THallCanvas::mouseMoveEvent(QMouseEvent *event) {
	int st = wnd->getCurrentTool();

	switch (st) {
		case 0:
		case 1: {
			int fill = (st == 0) ? 1 : 0;
			int start_x = event->buttons() == Qt::RightButton ? r_start_x : ((event->x() + ox) / cs);
			int start_y = event->buttons() == Qt::RightButton ? r_start_y : ((event->y() + oy) / cs);

			int end_x = ((event->x() + ox) / cs) + 1;
			int end_y = ((event->y() + oy) / cs) + 1;

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

			if (event->buttons() == Qt::RightButton) {
				for (int x = 0; x < w * h; x++) {
					int m = map[x], f = 0;

					switch (m) {
						case 0:
							f = 0;
							break;
						case 1:
							f = 1;
							break;
						case 2:
							f = 0;
							break;
						case 3:
							f = 1;
							break;
						default:;
					}

					map[x] = f;
				}

				for (int x = start_x; x < end_x; x++)
					for (int y = start_y; y < end_y; y++) {
						int m = getCell(x, y), f = 0;

						switch (m) {
							case 0:
								f = 2;
								break;
							case 1:
								f = 3;
								break;
							default:;
						}

						setCell(x, y, f);
					}

			} else {
				setCell(start_x, start_y, fill);
			}

			lastFill = (st) ? 0 : 1;

		}
			break;
		case 2:

			break;
		default:
			qDebug() << "Unsupported, " + QString::number(st);
	}



	update();
}

void THallCanvas::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event)

	r_start_x = -1;
	r_start_y = -1;

	for (int x = 0; x < w * h; x++) {
		int m = map[x], f = 0;

		switch (m) {
			case 0:
				f = 0;
				break;
			case 1:
				f = 1;
				break;
			case 2:
				f = lastFill;
				break;
			case 3:
				f = lastFill;
				break;
			default:;
		}

		map[x] = f;
	}

	update();
}

void THallCanvas::setSize(int w, int h) {
	int *nmap = new int[w * h], *omap = map;
	int ow = this->w, oh = this->h;

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

void THallCanvas::wheelEvent(QWheelEvent *event) {
	double inc = event->delta() > 0 ? cs * 1.25 : cs * 0.8;
	inc -= cs;

	int tox = ((event->x() + ox) / cs), toy = ((event->y() + oy) / cs);

	// Cell size
	cs += inc;
	cs = cs < 6 ? 6 : cs;
	cs = cs > 40 ? 40 : cs;

	// Offset
	ox = tox * cs - event->x();
	oy = toy * cs - event->y();

	update();

	wnd->changeScale(cs * w - width() + 200, cs * h - height() + 200);
	wnd->setScroll(ox, oy);
	event->accept();
}

void THallCanvas::moveView(int x, int y) {
	ox += x * (cs * 1.1);
	oy += y * (cs * 1.1);

	update();
}

QJsonObject THallCanvas::toJson() {
	QJsonObject o;

	o["width"] = w;
	o["height"] = h;

	o["cs"] = cs;

	QJsonArray r;
	int st = -1, ln = 0;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int c = getCell(x, y);

			if (c == 1) {
				if (st == -1) {
					st = x;
				}

				ln++;

			}

			if ((c == 0 && st != -1) || ((x == (w - 1)) && ln != 0)) {
				QJsonObject t;

				t["l"] = ln;
				t["x"] = st;
				t["y"] = y;

				st = -1;
				ln = 0;

				r << t;
			}
		}
	}

	o["sectors"] = r;

	return o;
}

void THallCanvas::fromJson(QJsonObject o) {
	w = o["width"].toInt();
	h = o["height"].toInt();

	cs = o["cs"].toInt(20);

	map = new int[w * h];
	for (int i = 0; i < w * h; i++)
		map[i] = 0;

	for (QJsonValue v : o["sectors"].toArray()) {
		QJsonObject t = v.toObject();

		int tx = t["x"].toInt(), ty = t["y"].toInt(), tl = t["l"].toInt();

		for (int x = tx; x < tx + tl; x++)
			setCell(x, ty, 1);
	}

	update();
}

void THallCanvas::scrollW(int p) {
	ox = p;
	update();
}

void THallCanvas::scrollH(int p) {
	oy = p;
	update();
}
