#ifndef THEATRE_ADMIN_THALLTOOLS_H
#define THEATRE_ADMIN_THALLTOOLS_H

#include <windows/hall/draw/THall.h>

class THallTools : public QWidget {
	QButtonGroup *bg;

	// Tool 3 - Seats
	QWidget *seat_w;
	QLineEdit *seat_start;
	QComboBox *seat_direc;

	// Tool 4 - Sectors
	QWidget *sect_w;
	QComboBox *sect_box;
	QMap<int, THallSect> sect_list;

public:
	THallTools();

	int getCurrentId();

	void setCurrentId(int i);

	THallSeatSett getSeatSettings();

	QMap<int, THallSect> getSectors();

	QPair<int, THallSect *> getCurrentSect();

	QJsonArray toJson();

	void fromJson(QJsonArray o);

	void updateSect();
};

class THallToolSect : public QDialog {
	QLineEdit *l_name, *l_pref;
	QColor l_color;

public:
	THallToolSect();

	static THallSect getNewSect();

};

#endif //THEATRE_ADMIN_THALLTOOLS_H
