#ifndef THEATRE_ADMIN_TPRICE_H
#define THEATRE_ADMIN_TPRICE_H

#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtCore/QList>

#define GET_C(c) QColor(c, c, c)

struct TPriceSeat {
	bool left;
	int x, y, st;

	TPriceSeat() {}

	TPriceSeat(int s, int tx, int ty, bool tl = true) : st(s), x(tx), y(ty), left(tl) {}

	static TPriceSeat fromString(QString s) {
		auto l = s.split(':');
		return TPriceSeat(l[0].toInt(), l[1].toInt(), l[2].toInt(), l[3].toInt() == 1);
	}

	QString toString() {
		return QString("%1:%2:%3:%4").arg(st).arg(x).arg(y).arg(left ? 1 : 0);
	}
};

struct TPriceSeatSett {
	bool left;
	int st;

	TPriceSeatSett(int ts, bool tl) : st(ts), left(tl) {}
};

struct TPriceCoord {
	int x, y;

	TPriceCoord() : x(0), y(0) {}

	TPriceCoord(int tx, int ty) : x(tx), y(ty) {}

	bool operator==(const TPriceCoord o) { return o.x == x && o.y == y; }

	static TPriceCoord fromString(QString s) {
		auto l = s.split(':');
		return TPriceCoord(l[0].toInt(), l[1].toInt());
	}

	QString toString() {
		return QString("%1:%2").arg(x).arg(y);
	}
};

struct TPriceSect {
	QString name, pref;
	QColor color;
	QList<TPriceCoord> coords;

	TPriceSect() {}

	TPriceSect(QString tn, QString tp, QColor tc) : name(tn), pref(tp), color(tc) {}
};

#include <QtWidgets/QtWidgets>
#include <windows/price/draw/THallPriceCanvas.h>
#include <windows/price/draw/THallPriceTools.h>

class THallPriceCanvas;

class THallPriceTools;

class THallPrice : public QWidget {
	THallPriceCanvas *w_canvas;
	THallPriceTools *w_tools;

public:
	THallPrice();

	QMap<int, TPriceSect> getSectors();

	QMap<int, TPriceSect> getPrices();

	int getCurrentPrice();

	void fromJson(QJsonObject o);

	void loadHall(QJsonObject o);

	QJsonObject toJson();

	void clear();

protected:
	void keyReleaseEvent(QKeyEvent *event) override;
};


#endif //THEATRE_ADMIN_TPRICE_H
