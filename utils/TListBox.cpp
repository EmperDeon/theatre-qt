#include "TListBox.h"
#include "TDB.h"

TListBox::TListBox(QString t) : QGroupBox("Редактирование списка") {
	QVBoxLayout *l = new QVBoxLayout;
	QHBoxLayout *hl = new QHBoxLayout;

	QPushButton *b_add = new QPushButton("Добавить");
	QPushButton *b_rem = new QPushButton("Удалить");
	list = new QListWidget;

	connect(b_add, &QPushButton::clicked, this, &TListBox::add);
	connect(b_rem, &QPushButton::clicked, this, &TListBox::rem);

	hl->addWidget(b_add);
	hl->addWidget(b_rem);

	QPushButton *b = new QPushButton("debug");
	connect(b, &QPushButton::clicked, this, [=]() {
		qDebug() << getAdded();
		qDebug() << getItems();
	});
	hl->addWidget(b);

	l->addLayout(hl);
	l->addWidget(list);

	setLayout(l);

	if (t != "")
		load(t);
}

void TListBox::load(QString t) {
	QJsonArray a = TDB().request("lists/" + t).toArray();

	for (QJsonValue v : a) {
		map.insert(v.toObject()["name"].toString(), QString::number(v.toObject()["id"].toInt()));
		list->addItem(v.toObject()["name"].toString());
	}
}

void TListBox::add() {
	QString n = QInputDialog::getText(this, "Добавление строки", "Название:");

	if (n != "") {
		list->addItem(n);
		added << n;
	}
}

void TListBox::rem() {
	auto selected = list->selectedItems();
	if (selected.size() == 0)
		return;

	QString curr = selected.value(0)->text();

	if (QMessageBox::question(this, "Удаление строки", QString("Вы точно хотите удалить строку \n \"%1\"").arg(curr)) ==
	    QMessageBox::Yes) {
		delete selected.value(0);

		if (!added.contains(curr)) {
			removed << curr;
		} else {
			added.removeOne(curr);
		}
	}
}

QStringList TListBox::getAdded() {
	QStringList r;

	for (QString s : added) {
		if (!map.contains(s))
			r << s;
	}

	return r;
}

QStringList TListBox::getItems() {
	QStringList r;

	for (QString s : removed) {
		r << map[s];
	}

	return r;
}
