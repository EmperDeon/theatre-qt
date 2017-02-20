#ifndef THEATRE_ADMIN_TWSETTINGS_H
#define THEATRE_ADMIN_TWSETTINGS_H

#include <QtWidgets/QtWidgets>

class TWSettings : public QFrame {
	QJsonObject sett;


public:
	TWSettings();

	void save();

	void reset();

	QComboBox *s_main_w;

	void fillMainW();

	void load();
};


#endif //THEATRE_ADMIN_TWSETTINGS_H
