#include <utils/TDB.h>
#include "TChoose.h"


TChoose::TChoose() {
	QVBoxLayout *l = new QVBoxLayout;
	list = new TComboBox("theatres");
	b_sub = new QPushButton("ОК");

	list->setMaximumWidth(250);
	b_sub->setMaximumWidth(200);

	list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	b_sub->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	l->setAlignment(Qt::AlignCenter);

	l->addWidget(new QLabel("Театр:"));
	l->addWidget(list);
	l->addWidget(b_sub, 0, Qt::AlignHCenter);

	connect(b_sub, &QPushButton::clicked, this, &TChoose::submit);

	setLayout(l);
}

void TChoose::submit() {
	if (QMessageBox::question(this, "Изменение текущего театра", "Вы уверены, что хотите изменить текущий театр ?") ==
	    QMessageBox::Yes) {
		QString o = TDB().request("theatres/change", {
				{"id", list->getIndex()}
		}).toString();

		if (o == "successful")
			QMessageBox::information(this, "Изменение текущего театра", "Успешно изменено");
	}
}
