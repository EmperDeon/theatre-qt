#include "THallPriceCanvas.h"

typedef QPair<int, int> TP;

void THallPriceCanvas::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, false);

	// Offset
	mw = (w * cs) - width() + 200;
	mh = (h * cs) - height() + 200;

	off_x = off_x > mw ? mw : off_x;
	off_y = off_y > mh ? mh : off_y;

	off_x = off_x < 0 ? 0 : off_x;
	off_y = off_y < 0 ? 0 : off_y;
	// Offset


	// Grid
	p.setPen(Qt::NoPen);
	p.setBrush(QBrush(GET_C(233))); // 235

	p.drawRect(0, 0, width(), height());
	p.setPen(QPen(GET_C(243)));

	p.translate(-off_x, -off_y);

	for (int x = 1; x <= w; x++)
		p.drawLine(x * cs, 1, x * cs, h * cs - 2);

	for (int y = 1; y <= h; y++)
		p.drawLine(1, y * cs, w * cs - 2, y * cs);

	// Seats
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++) {
			int i = getCell(x, y);
			if (i == 1) {
//				p.setBrush(QBrush(QColor(170, 170, 255)));
				p.setBrush(QBrush(GET_C(175)));

			} else if (i == 2 || i == 3) {
				p.setBrush(QBrush(GET_C(200)));

			} else {
				p.setBrush(QBrush(GET_C(223)));

			}

			p.drawRect(x * cs, y * cs, cs, cs);
		}
	// Seats


	// Sectors
	for (int i = 0; i < w * h; i++)
		sect_s[i] = seat_t[i] = seat_r[i] = 0;

	const QMap<int, TPriceSect> &map = wnd->getSectors();
	for (int s : map.keys()) {
		for (TPriceCoord c : map[s].coords) {
			if (price_s[c.x + c.y * w] == 0) {
				p.setBrush(map[s].color);
				p.drawRect(c.x * cs, c.y * cs, cs, cs);
			}
			sect_s[c.x + c.y * w] = s + 1;
		}
	}

	const QMap<int, TPriceSect> &pr = wnd->getPrices();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (int t = price_s[x + y * w]) {
				p.setBrush(t >= 100 ? GET_C(200) : pr[t].color);
				p.drawRect(x * cs, y * cs, cs, cs);
			}
		}
	}

	QMap<int, TP> sect_r;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (int t = sect_s[x + y * w]) {
				if (sect_r.contains(t)) {
					if (sect_r[t].second >= x)
						sect_r[t].first++;

					sect_r[t].second = x;
				} else {
					sect_r[t] = TP(1, x);
				}

				seat_r[x + y * w] = sect_r[t].first;
			}
		}
	}
	// Sectors


	// Draw border around
	p.setPen(GET_C(172));
	p.setBrush(Qt::NoBrush);

	p.drawRect(off_x, off_y, off_x + width() - 1, off_y + height() - 1);

	if (cs > 15) {

		// Form text overlay data
		for (TPriceSeat s : seat_n) {
			int x = s.x, y = s.y, st = s.st, i = getCell(x, y), curr_s = sect_s[x + y * w];

			while ((i == 0 || i == 1 || i == 3) && x > -1 && x < w && sect_s[x + y * w] == curr_s) {
				seat_t[x + y * w] = st++;

				x += s.left ? -1 : 1;
				i = getCell(x, y);

				if (i == 0 || curr_s == 0) {
					break;
				}
			}
		}

		// Draw text overlay
		p.setPen(Qt::white);
		p.setFont(QFont("Tahoma", int(cs * 0.35)));

		for (int x = 0; x < w; x++)
			for (int y = 0; y < h; y++) {
				if (int i = seat_t[x + y * w]) {
					p.drawText(x * cs + cs / 2, y * cs + cs / 2, cs / 2, cs / 2, Qt::AlignCenter, QString::number(i));
				}
				if (int i = seat_r[x + y * w]) {
					p.drawText(x * cs, y * cs, cs / 2, cs / 2, Qt::AlignCenter, QString::number(i));
				}
			}
	}

	// Finish drawing
	p.end();
	event->accept();
}

int THallPriceCanvas::getCell(int x, int y) const {
	if (x < w && y < h) {
		int i = seat_s[x + y * w];

		return i;
	} else
		return 0;
}

void THallPriceCanvas::setCell(int x, int y, int f) {
	if (x < w && y < h)
		seat_s[x + y * w] = f;
}

THallPriceCanvas::THallPriceCanvas(THallPrice *wn, QScrollBar *s_w, QScrollBar *s_h) : wnd(wn), scroll_w(s_w),
                                                                                       scroll_h(s_h) {}

void THallPriceCanvas::mousePressEvent(QMouseEvent *event) {
	r_start_x = ((event->x() + off_x) / cs);
	r_start_y = ((event->y() + off_y) / cs);

	mouseMoveEvent(event);
}

void THallPriceCanvas::mouseMoveEvent(QMouseEvent *event) {
	int fill = event->buttons() == Qt::RightButton ? 0 : wnd->getCurrentPrice();
	int start_x = event->modifiers() == Qt::ShiftModifier ? r_start_x : ((event->x() + off_x) / cs);
	int start_y = event->modifiers() == Qt::ShiftModifier ? r_start_y : ((event->y() + off_y) / cs);

	int end_x = ((event->x() + off_x) / cs) + 1;
	int end_y = ((event->y() + off_y) / cs) + 1;

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

	if (event->modifiers() == Qt::ShiftModifier) {
		for (int x = 0; x < w * h; x++) {
			int m = price_s[x], f = m;

			if (m >= 100)
				f = m - 100;

			price_s[x] = f;
		}

		for (int x = start_x; x < end_x; x++)
			for (int y = start_y; y < end_y; y++) {
				int m = price_s[x + y * w], f = 0;

				f = m + 100;

				price_s[x + y * w] = f;
			}

	} else {
		price_s[start_x + start_y * w] = fill;
	}

	lastFill = event->buttons() == Qt::RightButton ? 0 : wnd->getCurrentPrice();

	update();
}

void THallPriceCanvas::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event)

	r_start_x = -1;
	r_start_y = -1;

	for (int x = 0; x < w * h; x++) {
		int m = price_s[x], f = m;

		if (m >= 100) {
			f = lastFill;
		}

		price_s[x] = f;
	}

	update();
}

void THallPriceCanvas::swapIf(int &i1, int &i2) {
	int t = qMin(i1, i2);
	i2 = qMax(i1, i2);
	i1 = t;
}

void THallPriceCanvas::wheelEvent(QWheelEvent *event) {
	double inc = event->delta() > 0 ? cs * 1.25 : cs * 0.8;
	inc -= cs;

	int tox = ((event->x() + off_x) / cs), toy = ((event->y() + off_y) / cs);

	// Cell size
	cs += inc;
	cs = cs < 6 ? 6 : cs;
	cs = cs > 40 ? 40 : cs;

	// Offset
	off_x = tox * cs - event->x();
	off_y = toy * cs - event->y();

	update();

	scroll_w->setMaximum(mw);
	scroll_h->setMaximum(mh);
	scroll_w->setValue(off_x);
	scroll_h->setValue(off_y);

	event->accept();
}

void THallPriceCanvas::moveView(int x, int y) {
	off_x += x * (cs * 1.1);
	off_y += y * (cs * 1.1);

	update();
}

QJsonObject THallPriceCanvas::toJson() {
	QJsonObject o;

	o["width"] = w;
	o["height"] = h;

	o["cs"] = cs;

//	TODO: Add validations (all seats in sectors, all seats have names)
//	int *seat_t = new int[w * h];

	// Seats
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
				QString t("%1:%2:%3");
				t = t.arg(st).arg(y).arg(ln);

				st = -1;
				ln = 0;

				r << t;
			}
		}
	}

	o["seats"] = r;


	// Seat names
	r = QJsonArray();
	for (TPriceSeat s : seat_n) {
		r << s.toString();
	}

	o["seat_n"] = r;

	return o;
}

void THallPriceCanvas::fromJson(QJsonObject o) {
	// Clear old data
	seat_n.clear();
	sect_n.clear();

	// Fill with new data
	w = o["width"].toInt(150);
	h = o["height"].toInt(80);

	cs = o["cs"].toInt(20);

	if (seat_s == nullptr) {
		seat_s = new int[w * h];
		sect_s = new int[w * h];
		seat_t = new int[w * h];
		seat_r = new int[w * h];
		price_s = new int[w * h];
	}

}

void THallPriceCanvas::scrollW(int p) {
	off_x = p;
	update();
}

void THallPriceCanvas::scrollH(int p) {
	off_y = p;
	update();
}

QPair<int, TPriceSeat> THallPriceCanvas::getSeatAt(int cx, int cy) {
	for (int i = 0; i < seat_n.count(); i++) {
		TPriceSeat s = seat_n.at(i);
		if (s.x == cx && s.y == cy)
			return QPair<int, TPriceSeat>(i, s);
	}

	return QPair<int, TPriceSeat>(-1, TPriceSeat());
}

void THallPriceCanvas::loadHall(QJsonObject o) {
	// Clear old data
	seat_n.clear();
	sect_n.clear();

	// Fill with new data
	w = o["width"].toInt(150);
	h = o["height"].toInt(80);

	cs = o["cs"].toInt(20);

	if (seat_s == nullptr) {
		seat_s = new int[w * h];
		sect_s = new int[w * h];
		seat_t = new int[w * h];
		seat_r = new int[w * h];
		price_s = new int[w * h];
	}

	for (int i = 0; i < w * h; i++)
		seat_s[i] = price_s[i] = 0;

	for (QJsonValue v : o["seats"].toArray()) {
		auto t = v.toString().split(":");

		int tx = t[0].toInt(), ty = t[1].toInt(), tl = t[2].toInt();

		for (int x = tx; x < tx + tl; x++)
			setCell(x, ty, 1);
	}

	// Seat Names
	for (QJsonValue v : o["seat_n"].toArray()) {
		seat_n << TPriceSeat::fromString(v.toString());
	}

	update();

}
