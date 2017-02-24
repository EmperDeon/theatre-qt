#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include "TConfig.h"

QJsonObject TConfig::load() {
	QFile f("config.json");
	if (f.exists()) {
		f.open(QFile::ReadOnly);
		return QJsonDocument::fromJson(f.readAll()).object();

	} else {
		return QJsonObject();
	}
}

void TConfig::save(QJsonObject o) {
	QFile f("config.json");
	f.open(QFile::WriteOnly);
	f.write(QJsonDocument(o).toJson());
	f.close();
}

QJsonValue TConfig::get(QString key, QJsonValue def) {
	QJsonObject obj = load();

	return obj.contains(key) ? obj.value(key) : def;
}

QString TConfig::getS(QString key, QString def) {
	QJsonObject obj = load();

	return obj.contains(key) ? obj.value(key).toString(def) : def;
}

void TConfig::set(QString key, QJsonValue val) {
	QJsonObject obj = load();

	obj.insert(key, val);

	save(obj);
}

void TConfig::rem(QString key) {
	QJsonObject obj = load();

	obj.remove(key);

	save(obj);
}

