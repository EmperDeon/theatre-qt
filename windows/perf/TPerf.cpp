#include <utils/TDB.h>
#include "TPerf.h"

TPerf::TPerf(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();

	l_name = new QLineEdit(o["name"].toString());
	l_auth = new QLineEdit(o["author"].toString());
	l_type = new QLineEdit(o["type"].toString());

	e_desc_s = new QTextEdit(o["desc_s"].toString());

	l_name->setEnabled(false);
	l_auth->setEnabled(false);
	l_type->setEnabled(false);

	e_desc_s->setEnabled(false);
	e_desc_s->setMaximumHeight(100);

	b_edt = new QPushButton("Изменить");
	b_del = new QPushButton("Удалить");

	b_edt->setMaximumWidth(100);
	b_del->setMaximumWidth(100);

	connect(b_edt, &QPushButton::clicked, this, &TPerf::edt);
	connect(b_del, &QPushButton::clicked, this, &TPerf::del);

	QFormLayout *fl1 = new QFormLayout;
	fl1->addRow("Название:", l_name);
	fl1->addRow("Автор:", l_auth);
	fl1->addRow("Тип:", l_type);
	fl1->addRow("Краткое описание:", e_desc_s);


	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);
	vl->addWidget(b_edt);
	vl->addWidget(b_del);

	l->addLayout(fl1);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}

void TPerf::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	e_desc_s->setEnabled(!sv);
}

void TPerf::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("t_perfs/edit",
		                          {
				                          {"id",     QString::number(id)},
				                          {"desc_s", e_desc_s->toPlainText()}
		                          }
		).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}

void TPerf::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("t_perfs/delete", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}
}