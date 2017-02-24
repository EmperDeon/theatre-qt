#include "THall.h"

THall::THall() {
	QVBoxLayout *l = new QVBoxLayout;

	w_canvas = new THallCanvas(this);
	w_tools = new THallTools;

	l->addWidget(w_tools);
	l->addWidget(w_canvas);

	l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);

	setLayout(l);
}

void THall::setSize(int w, int h) {

}

void THall::crop() {

}
