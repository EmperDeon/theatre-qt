#include "THallCanvas.h"

typedef QPair<int, int> TP;

void THallCanvas::paintEvent(QPaintEvent *event) {
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

	const QMap<int, THallSect> &map = wnd->getSectors();
	for (int s : map.keys()) {
		for (THallCoord c : map[s].coords) {
			p.setBrush(map[s].color);

			p.drawRect(c.x * cs, c.y * cs, cs, cs);

			sect_s[c.x + c.y * w] = s + 1;
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
		for (THallSeat s : seat_n) {
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

int THallCanvas::getCell(int x, int y) const {
	if (x < w && y < h) {
		int i = seat_s[x + y * w];

		return i;
	} else
		return 0;
}

void THallCanvas::setCell(int x, int y, int f) {
	if (x < w && y < h)
		seat_s[x + y * w] = f;
}

THallCanvas::THallCanvas(THall *wn, QScrollBar *s_w, QScrollBar *s_h) : wnd(wn), scroll_w(s_w), scroll_h(s_h) {}

void THallCanvas::mousePressEvent(QMouseEvent *event) {
	r_start_x = ((event->x() + off_x) / cs);
	r_start_y = ((event->y() + off_y) / cs);

	mouseMoveEvent(event);
}

void THallCanvas::mouseMoveEvent(QMouseEvent *event) {
	int st = wnd->getCurrentTool();

	switch (st) {
		case 0:
		case 1: {
			int fill = (st == 0) ? 1 : 0;
			int start_x = event->buttons() == Qt::RightButton ? r_start_x : ((event->x() + off_x) / cs);
			int start_y = event->buttons() == Qt::RightButton ? r_start_y : ((event->y() + off_y) / cs);

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

			if (event->buttons() == Qt::RightButton) {
				for (int x = 0; x < w * h; x++) {
					int m = seat_s[x], f = 0;

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

					seat_s[x] = f;
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
		case 2: {
			int cx = (event->x() + off_x) / cs, cy = ((event->y() + off_y) / cs);
			QPair<int, THallSeat> seat = getSeatAt(cx, cy);
			THallSeatSett sett = wnd->getSeatSettings();

			if (event->buttons() == Qt::RightButton) {
				if (seat.first != -1)
					seat_n.removeAt(seat.first);

			} else {
				THallSeat t = seat.second;

				t.st = sett.st;
				t.left = sett.left;
				t.x = cx;
				t.y = cy;

				if (seat.first == -1) {
					seat_n.append(t);

				} else {
					seat_n.replace(seat.first, t);
				}
			}
		}
			break;

		case 3: {
			int cx = (event->x() + off_x) / cs, cy = ((event->y() + off_y) / cs);
			auto sect = wnd->getCurrentSect();

			if (sect.first == -1)
				break;

			auto s = &sect.second->coords;

			THallCoord t = THallCoord(cx, cy);

			if (event->buttons() == Qt::LeftButton) {
				if (!sect_n.contains(t)) {
					sect_n.append(t);
					s->append(t);

				}
			} else {
				if (s->contains(t)) {
					sect_n.removeOne(t);
					s->removeOne(t);
				}
			}
		}
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
		int m = seat_s[x], f = 0;

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

		seat_s[x] = f;
	}

	update();
}

void THallCanvas::setSize(int w, int h) {
	int *nmap = new int[w * h], *omap = seat_s;
	int ow = this->w, oh = this->h;

	// Clear new seat_s
	for (int i = 0; i < w * h; i++)
		nmap[i] = 0;

	// Fill with old data
	for (int x = 0; x < qMin(ow, w); x++)
		for (int y = 0; y < qMin(oh, h); y++) {
			nmap[x + w * y] = omap[x + ow * y];
		}

	this->w = w;
	this->h = h;
	this->seat_s = nmap;
	delete omap;


	delete sect_s;
	delete seat_t;
	delete seat_r;

	sect_s = new int[w * h];
	seat_t = new int[w * h];
	seat_r = new int[w * h];

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

void THallCanvas::moveView(int x, int y) {
	off_x += x * (cs * 1.1);
	off_y += y * (cs * 1.1);

	update();
}

QJsonObject THallCanvas::toJson() {
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
	for (THallSeat s : seat_n) {
		r << s.toString();
	}

	o["seat_n"] = r;

	return o;
}

void THallCanvas::fromJson(QJsonObject o) {
	// Clear old data
	seat_n.clear();
	sect_n.clear();

	// Fill with new data
	w = o["width"].toInt(150);
	h = o["height"].toInt(80);

	cs = o["cs"].toInt(20);

	if (seat_s != nullptr) {
		delete seat_s;
		delete sect_s;
		delete seat_t;
		delete seat_r;
	}

	seat_s = new int[w * h];
	sect_s = new int[w * h];
	seat_t = new int[w * h];
	seat_r = new int[w * h];

	for (int i = 0; i < w * h; i++)
		seat_s[i] = 0;

	for (QJsonValue v : o["seats"].toArray()) {
		auto t = v.toString().split(":");

		int tx = t[0].toInt(), ty = t[1].toInt(), tl = t[2].toInt();

		for (int x = tx; x < tx + tl; x++)
			setCell(x, ty, 1);
	}

	// Seat Names
	for (QJsonValue v : o["seat_n"].toArray()) {
		seat_n << THallSeat::fromString(v.toString());
	}

	update();
}

void THallCanvas::scrollW(int p) {
	off_x = p;
	update();
}

void THallCanvas::scrollH(int p) {
	off_y = p;
	update();
}

QPair<int, THallSeat> THallCanvas::getSeatAt(int cx, int cy) {
	for (int i = 0; i < seat_n.count(); i++) {
		THallSeat s = seat_n.at(i);
		if (s.x == cx && s.y == cy)
			return QPair<int, THallSeat>(i, s);
	}

	return QPair<int, THallSeat>(-1, THallSeat());
}
