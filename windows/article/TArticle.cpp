#include "TArticle.h"

TArticle::TArticle(QJsonObject o) {
	QHBoxLayout *l = new QHBoxLayout;

	id = o["id"].toInt();

	title = new QLineEdit(o["name"].toString());
	desc = new QTextEdit(o["desc_s"].toString());


	b_edt = new QPushButton("Изменить");
	b_del = new QPushButton("Удалить");

	title->setEnabled(false);
	desc->setEnabled(false);

	b_edt->setMaximumWidth(100);
	b_del->setMaximumWidth(100);

	connect(b_edt, &QPushButton::clicked, this, &TArticle::edt);
	connect(b_del, &QPushButton::clicked, this, &TArticle::del);

	QFormLayout *fl1 = new QFormLayout;
	fl1->addRow("Заголовок", title);
	fl1->addRow("Краткое описание:", desc);


	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);
	vl->addWidget(b_edt);
	vl->addWidget(b_del);

	l->addLayout(fl1);
	l->addLayout(vl);
	l->addSpacing(10);

	setLayout(l);
}

void TArticle::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	title->setEnabled(!sv);
	desc->setEnabled(!sv);
}

void TArticle::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("articles/delete", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}
}

void TArticle::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("articles/edit",
		                          {
				                          {"id",     QString::number(id)},
				                          {"name",   title->text()},
				                          {"desc_s", desc->toPlainText()}


		                          }).toString();

		if (o == "successful")
			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
	}
}
