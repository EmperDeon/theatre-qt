#include <utils/TDB.h>
#include "TPerfCreate.h"

TPerfCreate::TPerfCreate() {
	// Global performance
	QGroupBox *gr = new QGroupBox("Спектакль");
	p_wgt = new QWidget;
	QVBoxLayout *gv = new QVBoxLayout;
	QHBoxLayout *gh = new QHBoxLayout;
	QFormLayout *gf = new QFormLayout;

	p_box = new TComboBox("performances");
	p_add = new QPushButton("Добавить в список");

	p_name = new QLineEdit;
	p_auth = new QLineEdit;
	p_type = new TComboBox("p_types");

	connect(p_add, &QPushButton::clicked, this, &TPerfCreate::add);

	p_add->setMaximumWidth(135);

	p_wgt->setLayout(gf);
	p_wgt->setVisible(false);

	gh->addWidget(p_box);
	gh->addWidget(p_add);

	gf->addRow("Название:", p_name);
	gf->addRow("Автор:", p_auth);
	gf->addRow("Тип:", p_type);

	gv->addLayout(gh);
	gv->addWidget(p_wgt);

	gr->setLayout(gv);
	// Global performance

	// Theatre performance
	e_desc = new QTextEdit;
	e_desc_s = new QTextEdit;

	e_desc_s->setMaximumHeight(100);
	// Theatre performance

	layout->addWidget(gr);

	layout->addWidget(new QLabel("Краткое описание:"));
	layout->addWidget(e_desc_s);

	layout->addWidget(new QLabel("Полное описание:"));
	layout->addWidget(e_desc);
}

void TPerfCreate::add() {
	bool sv = p_add->text() == "Добавить в список";

	p_add->setText(sv ? "Выбрать из списка" : "Добавить в список");

	p_box->setEnabled(!sv);
	p_wgt->setVisible(sv);
}

void TPerfCreate::reset() {
	p_box->setEnabled(true);
	p_wgt->setVisible(false);
	p_add->setText("Добавить в список");

	p_box->setCurrentIndex(0);
	p_name->clear();
	p_auth->clear();
	p_type->setCurrentIndex(0);

	e_desc->clear();
	e_desc_s->clear();
}

QString TPerfCreate::getPath() {
	return "t_perfs";
}

QMap<QString, QString> TPerfCreate::getParams() {
	QMap<QString, QString> map;

	if (p_wgt->isVisible()) {
		map["name"] = p_name->text();
		map["author"] = p_auth->text();
		map["type_id"] = p_type->getIndex();

	} else {
		map["perf_id"] = p_box->getIndex();
	}

	map["desc"] = e_desc->toPlainText();
	map["desc_s"] = e_desc_s->toPlainText();

	return map;
}
