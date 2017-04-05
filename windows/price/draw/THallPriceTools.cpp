#include "THallPriceTools.h"

THallPriceTools::THallPriceTools() {
	QHBoxLayout *l = new QHBoxLayout;
	l_price = new QHBoxLayout;
	bg = new QButtonGroup;

	bg->setExclusive(true);

	QPushButton *b_add = new QPushButton(QIcon(":/p_add.png"), ""), *b_edt = new QPushButton(QIcon(":/h_pen.png"), "");

	b_add->setFixedSize(40, 40);
	b_add->setIconSize(QSize(30, 30));
	b_edt->setFixedSize(40, 40);
	b_edt->setIconSize(QSize(30, 30));

	connect(b_add, &QPushButton::clicked, this, &THallPriceTools::add);
	connect(b_edt, &QPushButton::clicked, this, &THallPriceTools::edt);

	l->addWidget(b_add);
	l->addWidget(b_edt);
	l->addLayout(l_price);

	l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);
	l->setAlignment(Qt::AlignLeft);

	l_price->setMargin(0);
	l_price->setContentsMargins(0, 0, 0, 0);
	l_price->setAlignment(Qt::AlignLeft);

	price_list[0] = TPriceSect();

	// Tmp
	price_list[1] = TPriceSect("200", "", QColor(255, 0, 0, 100));
	price_list[2] = TPriceSect("300", "", QColor(0, 255, 0, 100));
	price_list[3] = TPriceSect("350", "", QColor(0, 0, 255, 100));
	price_list[4] = TPriceSect("400", "", QColor(255, 127, 0, 100));
	// Tmp

	updateSects();

	setFixedHeight(45);
	setLayout(l);

}

void THallPriceTools::add() {
	TPriceSect t = TPriceToolSect::getSect();

	price_list.insert(price_list.size(), t);

	updateSects();
}

void THallPriceTools::edt() {
	TPriceSect t = TPriceToolSect::getSect(price_list[bg->checkedId()]);

	price_list[bg->checkedId()] = t;

	updateSects();
}

void THallPriceTools::updateSects() {
	for (QAbstractButton *b : bg->buttons()) {
		bg->removeButton(b);
		b->deleteLater();
	}

	for (int k : price_list.keys()) {
		TPriceSect s = price_list[k];
		if (s.name != "") {
			QPushButton *b = new QPushButton(s.name);

			b->setCheckable(true);
			b->setFixedSize(60, 40);
			b->setStyleSheet(
					"font-size: 14pt; font-weight: bold; background-color: " + s.color.name(QColor::HexArgb) + ";");

			bg->addButton(b, k);
			l_price->addWidget(b);
		}
	}

	bg->button(1)->setChecked(true);
}

QMap<int, TPriceSect> THallPriceTools::getSectors() {
	return sect_list;
}

QMap<int, TPriceSect> THallPriceTools::getPrices() {
	return price_list;
}

int THallPriceTools::getCurrentPrice() {
	if (price_list.size() == 0)
		return -1;
	else
		return bg->checkedId();
}

QJsonArray THallPriceTools::toJson() {
	QJsonArray r;

	for (int k : price_list.keys()) {
		TPriceSect v = price_list[k];
		QJsonObject o;

		o["id"] = k;
		o["price"] = v.name;
		o["color"] = v.color.name(QColor::HexArgb);

		r << o;
	}

	return r;
}

void THallPriceTools::fromJson(QJsonArray o) {

}

void THallPriceTools::loadHall(QJsonArray o) {
	sect_list.clear();

	for (QJsonValue sect : o) {
		TPriceSect s;
		QJsonObject obj = sect.toObject();

		s.name = obj["name"].toString();
		s.pref = obj["pref"].toString();
		s.color = QColor(obj["color"].toString());
		s.color.setAlpha(30);

		for (QJsonValue v : obj["coords"].toArray())
			s.coords << TPriceCoord::fromString(v.toString());

		sect_list.insert(obj["id"].toInt(), s);
	}
}


TPriceToolSect::TPriceToolSect(TPriceSect old) {
	QFormLayout *l = new QFormLayout;
	QHBoxLayout *hl = new QHBoxLayout;
	QButtonGroup *bg = new QButtonGroup;

	l_name = new QLineEdit;

	if (old.name != "")
		l_name->setText(old.name);

	QList <QColor> b_list;

	b_list << QColor(255, 0, 0);
	b_list << QColor(0, 255, 0);
	b_list << QColor(0, 0, 255);
	b_list << QColor(255, 127, 0);
	b_list << QColor(186, 0, 255);

	int i = 0;
	for (QColor c : b_list) {

		QPushButton *bt = new QPushButton;
		c.setAlpha(100);

		bt->setCheckable(true);
		bt->setFixedSize(30, 30);
		bt->setProperty("color", c);
		bt->setStyleSheet("background-color: " + c.name(QColor::HexArgb) + ";");
		bg->addButton(bt, i++);

		connect(bg, static_cast<void (QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
		        [=](QAbstractButton *id, bool checked) {
			        l_color = id->property("color").value<QColor>();
		        });

		if (c == old.color)
			bt->setChecked(true);

		hl->addWidget(bt);
	}

	if (old.name == "")
		bg->button(0)->setChecked(true);

	l->addRow("Цена: ", l_name);
	l->addRow("Цвет: ", hl);


	QPushButton *b_acc = new QPushButton("Сохранить"), *b_rej = new QPushButton("Отмена");

	connect(b_acc, &QPushButton::clicked, this, &TPriceToolSect::accept);
	connect(b_rej, &QPushButton::clicked, this, &TPriceToolSect::reject);

	l->addRow(b_acc, b_rej);


	setLayout(l);
}

TPriceSect TPriceToolSect::getSect(TPriceSect old) {
	auto t = new TPriceToolSect(old);
	int r = t->exec();

	if (r) {
		old.name = t->l_name->text();
		old.color = t->l_color.name(QColor::HexArgb);
	}

	return old;
}
