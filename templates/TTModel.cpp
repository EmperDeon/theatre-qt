#include <utils/TDB.h>
#include <windows/user/TUsers.h>
#include "TTModel.h"

TTModel::TTModel(QJsonObject o) {
	l = new QHBoxLayout;

	id = o["id"].toInt();


	layout = new QFormLayout;

	// Form
	l_upd = new QLabel;
	QLabel *l_upd_l = new QLabel("Последнее изменение:");

	l_upd->setEnabled(false);
	l_upd->setStyleSheet("font-size: 11px");
	l_upd->setText(o["timestamps"].toObject()["updated_at"].toString());

	l->addLayout(layout);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->setAlignment(Qt::AlignTop);

	l->addLayout(vl);

	l->addSpacing(10);

	setLayout(l);
	setFrameStyle(QFrame::StyledPanel);

	QTimer::singleShot(0, [=]() {
		layout->addRow(new QLabel(""));
		layout->addRow(l_upd_l, l_upd);

		if (TUsers::hasPerm(getPath() + "_edit")) {
			b_edt = new QPushButton("Изменить");
			b_del = new QPushButton("Удалить");

			b_edt->setMaximumWidth(100);
			b_del->setMaximumWidth(100);

			connect(b_edt, &QPushButton::clicked, this, &TTModel::edt);
			connect(b_del, &QPushButton::clicked, this, &TTModel::del);

			vl->addWidget(b_edt);
			vl->addWidget(b_del);
		}
	});
}

void TTModel::edt() {
	bool sv = b_edt->text() == "Сохранить";

	b_edt->setText(sv ? "Изменить" : "Сохранить");

	if (sv) {
		save();
	}

	setFEnabled(!sv);
}

void TTModel::del() {
	if (QMessageBox::question(this, "Удаление информации из БД", "Вы уверены, что хотите удалить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/destroy", {{"id", QString::number(id)}}).toString();

		if (o == "successful") {
//			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
			this->deleteLater();
		}
	}

}

void TTModel::save() {
	if (QMessageBox::question(this, "Сохранение в БД", "Вы уверены, что хотите сохранить эти данные ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request(getPath() + "/update", getParams()).toString();

		if (o == "successful") {
//			QMessageBox::information(this, "Сохранение в БД", "Успешно сохранено");
		}
	}
}

