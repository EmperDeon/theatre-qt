#ifndef THEATRE_ADMIN_THALLTOOLS_H
#define THEATRE_ADMIN_THALLTOOLS_H
#include <QtWidgets/QtWidgets>

struct THallSeatSett {
	bool left;
	int st;

	THallSeatSett(int ts, bool tl) : st(ts), left(tl) {}
};

class THallTools : public QWidget {
	QButtonGroup *bg;

	// Tool 3 - Seats
	QWidget *seat_w;
	QLineEdit *seat_start;
	QComboBox *seat_direc;

public:
	THallTools();

	int getCurrentId();

	void setCurrentId(int i);

	THallSeatSett getSeatSettings();
};


#endif //THEATRE_ADMIN_THALLTOOLS_H
