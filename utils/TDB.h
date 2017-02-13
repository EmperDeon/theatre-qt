#ifndef THEATRE_ADMIN_TDB_H
#define THEATRE_ADMIN_TDB_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QHttpPart>
#include <QJsonObject>
#include "TConfig.h"

class TDB {
	QNetworkAccessManager manager;
	QJsonObject lastReply;
	int lastTime;
	QNetworkReply::NetworkError lastError;

	QString token;
	TConfig conf;

	QStringList roles;

	QJsonValue GET(QString path, QMap<QString, QString> params, QString r_type);

	void getToken();

	void checkAndRefreshToken();

	bool hasErrors();

public:
	TDB();

	QJsonValue request(QString path, QMap<QString, QString> params = QMap<QString, QString>());

//	QJsonObject lastError();

	QStringList getPerms();


	void writeToLog(QString path, QMap<QString, QString> params, QString r_type);

	QString getResponseCode() const;

	QString getCodeDesc(QString path);

	QJsonValue uploadFiles(QMap<QString, QString> files, QMap<QString, QString> params = QMap<QString, QString>());

	// TODO: Maybe mak these static
	QJsonValue upload(QMap<QString, QIODevice *> io, QMap<QString, QString> params = QMap<QString, QString>());

	void appendStringPart(QHttpMultiPart *multipart, QString k, QString v) const;

	void appendFilePart(QHttpMultiPart *multipart, QString k, QIODevice *v) const;
};


#endif //THEATRE_ADMIN_TDB_H
