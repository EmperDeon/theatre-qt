#include <utils/TDB.h>
#include "TPerfApprove.h"

TPerfApprove::TPerfApprove() {
	QJsonArray arr = TDB().request("perfs/approval").toArray();

	for (QJsonValue v : arr)
		layout->addWidget(new TPerfApproveW(v.toObject()));
}

TPerfApproveW::TPerfApproveW(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();
	t_id = o["theatre_id"].toInt();

	QFormLayout *fl1 = new QFormLayout;
	QLineEdit *e_theatre = new QLineEdit(o["theatre"].toString());
	e_name = new QLineEdit(o["name"].toString());
	QLabel *l_upd = new QLabel;

	l_upd->setEnabled(false);
	l_upd->setStyleSheet("font-size: 11px");
	l_upd->setText(o["updated_at"].toString());

	fl1->addRow("Театр: ", e_theatre);
	fl1->addRow("Название: ", e_name);
	fl1->addRow("Последнее изменение: ", l_upd);


	QFormLayout *fl2 = new QFormLayout;
	e_author = new QLineEdit(o["author"].toString());
	e_type = new TComboBox("p_types");

	e_type->setCurrentItem(o["p_type"].toInt());

	fl2->addRow("Автор: ", e_author);
	fl2->addRow("Тип: ", e_type);


	e_theatre->setEnabled(false);
	e_author->setEnabled(false);
	e_name->setEnabled(false);
	e_type->setEnabled(false);


	QVBoxLayout *bl = new QVBoxLayout;
	QPushButton
			*b_app = new QPushButton("Одобрить"),
			*b_del = new QPushButton("Удалить");
	b_edt = new QPushButton("Изменить");

	connect(b_app, &QPushButton::clicked, this, &TPerfApproveW::approve);
	connect(b_del, &QPushButton::clicked, this, &TPerfApproveW::remove);
	connect(b_edt, &QPushButton::clicked, this, &TPerfApproveW::edit);

	bl->addWidget(b_app);
	bl->addWidget(b_del);
	bl->addWidget(b_edt);


	l->addLayout(fl1);
	l->addLayout(fl2);
	l->addLayout(bl);

	setLayout(l);
	setFrameStyle(QFrame::StyledPanel);
}

void TPerfApproveW::approve() {
	send(0);
}

void TPerfApproveW::remove() {
	send(-1);
}

void TPerfApproveW::edit() {
	bool b = b_edt->text() == "Изменить";
	b_edt->setText(b ? "Сохранить" : "Изменить");

	if (!b)
		send(t_id);

	e_author->setEnabled(b);
	e_name->setEnabled(b);
	e_type->setEnabled(b);
}

void TPerfApproveW::send(int a) {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QMap<QString, QString> map = {
				{"id",       QString::number(id)},
				{"approved", QString::number(a)}
		};

		if (e_name->isEnabled()) {
			map["name"] = e_name->text();
			map["author"] = e_author->text();
			map["p_type_id"] = e_type->getIndex();
		}

		QString o = TDB().request("perfs/approve", map).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}
