#ifndef THEATRE_ADMIN_THALL_H
#define THEATRE_ADMIN_THALL_H

#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtCore/QList>

#define GET_C(c) QColor(c, c, c)

struct THallSeat {
	bool left;
	int x, y, st;

	THallSeat() {}

	THallSeat(int s, int tx, int ty, bool tl = true) : st(s), x(tx), y(ty), left(tl) {}

	static THallSeat fromString(QString s) {
		auto l = s.split(':');
		return THallSeat(l[0].toInt(), l[1].toInt(), l[2].toInt(), l[3].toInt() == 1);
	}

	QString toString() {
		return QString("%1:%2:%3:%4").arg(st).arg(x).arg(y).arg(left ? 1 : 0);
	}
};

struct THallSeatSett {
	bool left;
	int st;

	THallSeatSett(int ts, bool tl) : st(ts), left(tl) {}
};

struct THallCoord {
	int x, y;

	THallCoord() : x(0), y(0) {}

	THallCoord(int tx, int ty) : x(tx), y(ty) {}

	bool operator==(const THallCoord o) { return o.x == x && o.y == y; }

	static THallCoord fromString(QString s) {
		auto l = s.split(':');
		return THallCoord(l[0].toInt(), l[1].toInt());
	}

	QString toString() {
		return QString("%1:%2").arg(x).arg(y);
	}
};

struct THallSect {
	QString name, pref;
	QColor color;
	QList<THallCoord> coords;

	THallSect() {}

	THallSect(QString tn, QString tp, QColor tc) : name(tn), pref(tp), color(tc) {}
};

#include <QtWidgets/QtWidgets>
#include <windows/hall/draw/THallCanvas.h>
#include <windows/hall/draw/THallTools.h>

class THallCanvas;
class THallTools;

class THall : public QWidget {
	THallCanvas *w_canvas;
	THallTools *w_tools;

public:
	THall();

	void setSize(int w, int h);

	void crop();

	int getCurrentTool();

	THallSeatSett getSeatSettings();

	QMap<int, THallSect> getSectors();;

	QPair<int, THallSect *> getCurrentSect();;

	void fromJson(QJsonObject o);

	QJsonObject toJson();

	void clear();

protected:
	void keyReleaseEvent(QKeyEvent *event) override;
};


#endif //THEATRE_ADMIN_THALL_H
