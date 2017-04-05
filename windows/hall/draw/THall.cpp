#include "THall.h"

THall::THall() {
	QVBoxLayout *l = new QVBoxLayout;

	w_tools = new THallTools;
	l->addWidget(w_tools);

	// Center
	QVBoxLayout *c_v = new QVBoxLayout;
	QVBoxLayout *c_v1 = new QVBoxLayout;
	QHBoxLayout *c_h = new QHBoxLayout;

	QScrollBar *s_w = new QScrollBar, *s_h = new QScrollBar;
	w_canvas = new THallCanvas(this, s_w, s_h);

	s_w->setOrientation(Qt::Horizontal);

	s_w->setFixedHeight(20);
	s_h->setFixedWidth(20);

	connect(s_w, &QScrollBar::valueChanged, w_canvas, &THallCanvas::scrollW);
	connect(s_h, &QScrollBar::valueChanged, w_canvas, &THallCanvas::scrollH);

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

	QTimer::singleShot(10, [this]() {
		this->setFocus();
	});

	setLayout(l);
}

void THall::setSize(int w, int h) {
	w_canvas->setSize(w, h);
}

void THall::crop() {

}

void THall::keyReleaseEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_1:
			w_tools->setCurrentId(0);
			break;
		case Qt::Key_2:
			w_tools->setCurrentId(1);
			break;
		case Qt::Key_3:
			w_tools->setCurrentId(2);
			break;

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

int THall::getCurrentTool() { return w_tools->getCurrentId(); }

THallSeatSett THall::getSeatSettings() { return w_tools->getSeatSettings(); }

QMap<int, THallSect> THall::getSectors() { return w_tools->getSectors(); }

QPair<int, THallSect *> THall::getCurrentSect() { return w_tools->getCurrentSect(); }

void THall::fromJson(QJsonObject o) {
	w_canvas->fromJson(o);
	w_tools->fromJson(o["sectors"].toArray());
}

QJsonObject THall::toJson() {
	QJsonObject a = w_canvas->toJson();
	a["sectors"] = w_tools->toJson();

	return a;
}

void THall::clear() {
	w_tools->fromJson(QJsonArray());
	w_canvas->fromJson(QJsonObject());
}
