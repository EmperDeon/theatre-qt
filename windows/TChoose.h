#ifndef TCHOOSE_H
#define TCHOOSE_H

#include <QtWidgets>
#include <utils/TComboBox.h>


class TChoose : public QWidget {
	TComboBox *list;
	QPushButton *b_sub;

public:
	TChoose();

	void submit();
};

#endif // TCHOOSE_H
