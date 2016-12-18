#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QDebug>
#include "TDCheck.h"

TDCheck::TDCheck(QMap<QString, QString> m, QStringList s) : map(m) {
	QVBoxLayout *l = new QVBoxLayout;

	QHBoxLayout *hl1 = new QHBoxLayout;
	QStringList n = map.keys();

	int size = 6; // Size of column

	for (int i = 0; i < (n.count() / size) + 1; i++) {
		QVBoxLayout *tl = new QVBoxLayout;
		tl->setAlignment(Qt::AlignTop);

		for (int j = 0; j < size; j++) {
			if (n.count() > (i * size + j)) {
				QCheckBox *tc = new QCheckBox(n[i * size + j]);
				tc->setChecked(s.contains(m[n[i * size + j]]));

				tl->addWidget(tc);
				lst << tc;
			}
		}

		hl1->addLayout(tl);
	}

	QHBoxLayout *hl2 = new QHBoxLayout;

	QPushButton *b_acc = new QPushButton(tr("ОК"));
	b_acc->setAutoDefault(true);

	QPushButton *b_rej = new QPushButton(tr("Отмена"));

	connect(b_acc, SIGNAL(clicked()), this, SLOT(accept()));
	connect(b_rej, SIGNAL(clicked()), this, SLOT(reject()));

	hl2->addWidget(b_acc);
	hl2->addWidget(b_rej);

	l->addLayout(hl1);
	l->addLayout(hl2);

	setLayout(l);
}

QStringList TDCheck::getSelection(QMap<QString, QString> m, QStringList s) {
	TDCheck t(m, s);

	if (t.exec()) {
		return t.getSelected();

	} else {
		return {""};
	}
}

QStringList TDCheck::getSelected() {
	QStringList r;

	for (QCheckBox *v : lst)
		if (v->isChecked())
			r << map[v->text()];

	return r;
}
