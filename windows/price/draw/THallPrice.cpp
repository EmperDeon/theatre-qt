#include "THallPrice.h"

THallPrice::THallPrice() {
	QVBoxLayout *l = new QVBoxLayout;

	w_tools = new THallPriceTools;
	l->addWidget(w_tools);

	// Center
	QVBoxLayout *c_v = new QVBoxLayout;
	QVBoxLayout *c_v1 = new QVBoxLayout;
	QHBoxLayout *c_h = new QHBoxLayout;

	QScrollBar *s_w = new QScrollBar, *s_h = new QScrollBar;
	w_canvas = new THallPriceCanvas(this, s_w, s_h);

	s_w->setOrientation(Qt::Horizontal);

	s_w->setFixedHeight(20);
	s_h->setFixedWidth(20);

	connect(s_w, &QScrollBar::valueChanged, w_canvas, &THallPriceCanvas::scrollW);
	connect(s_h, &QScrollBar::valueChanged, w_canvas, &THallPriceCanvas::scrollH);

	c_v->addWidget(w_canvas);
	c_v->addSpacing(2);
	c_v->addWidget(s_w);

	c_v1->addWidget(s_h);
	c_v1->addSpacing(20);

	c_h->addLayout(c_v);
	c_h->addSpacing(2);
	c_h->addLayout(c_v1);

	l->addLayout(c_h);
	// Center

	l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);
	l->setSpacing(0);

	setLayout(l);
}

void THallPrice::keyReleaseEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Right:
			w_canvas->moveView(1, 0);
			break;
		case Qt::Key_Down:
			w_canvas->moveView(0, 1);
			break;
		case Qt::Key_Left:
			w_canvas->moveView(-1, 0);
			break;
		case Qt::Key_Up:
			w_canvas->moveView(0, -1);
			break;
		default:;
	}
}

QMap<int, TPriceSect> THallPrice::getSectors() { return w_tools->getSectors(); }

void THallPrice::fromJson(QJsonObject o) {
	w_canvas->fromJson(o);
	w_tools->fromJson(o["sectors"].toArray());
}

QJsonObject THallPrice::toJson() {
	QJsonObject a;
	a["seats"] = w_canvas->toJson();
	a["prices"] = w_tools->toJson();

	return a;
}

void THallPrice::clear() {
	w_tools->fromJson(QJsonArray());
	w_canvas->fromJson(QJsonObject());
}

void THallPrice::loadHall(QJsonObject o) {
	w_canvas->loadHall(o);
	w_tools->loadHall(o["sectors"].toArray());
}

QMap<int, TPriceSect> THallPrice::getPrices() {
	return w_tools->getPrices();
}

int THallPrice::getCurrentPrice() {
	return w_tools->getCurrentPrice();
}
