#include <QtCore/QUrlQuery>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QMessageBox>
#include "dialogs/TDLogin.h"
#include "TDB.h"

TDB::TDB() {
	token = conf.getS("token");
}

QJsonObject TDB::request(QString path, QMap<QString, QString> params) {
	checkAndRefreshToken();

	qDebug() << "Reqest:" << path << ", params:" << params;

	params.insert("token", token);
	return GET(path, params);
}

QJsonObject TDB::GET(QString path, QMap<QString, QString> params) {
	QUrl c("https://laravel-theatre.herokuapp.com/api/" + path);
	QUrlQuery q;
	for (QString k : params.keys())
		q.addQueryItem(k, params[k]);

	c.setQuery(q);

	QNetworkReply *reply = manager.get(QNetworkRequest(c));
	QEventLoop wait;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(10000, &wait, SLOT(quit()));
	wait.exec();
	lastReply = QJsonDocument::fromJson(reply->readAll()).object();
	reply->deleteLater();

	hasErrors(lastReply);

	return lastReply;
}

QJsonObject TDB::lastError() {
	return QJsonObject{{"error",   lastReply["error"]},
	                   {"message", lastReply["message"]}};
}

void TDB::getToken() {
	QJsonObject cred = TDLogin::getCredentials();
	if (cred.isEmpty()) {
		exit(0); // TODO: prettify

	} else {
		conf.set("login", cred["login"]);

		QJsonObject o = GET("auth/new", QMap<QString, QString>{
				{"login",    cred["login"].toString()},
				{"password", cred["password"].toString()}
		});

		if (hasErrors(o)) {
			getToken();

		} else {
			token = o["token"].toString();
			conf.set("token", token);

		}
	}
}

void TDB::checkAndRefreshToken() {
	QJsonObject o = GET("auth/check", {{"token", token}});

	if (hasErrors(o)) {
		checkAndRefreshToken();

	}
}

bool TDB::hasErrors(QJsonObject o) {
	if (o.contains("error")) {
		QString err = o["error"].toString(), mess;

		if (err == "token_expired") {
			refreshToken();
			return true;
		}

		if (err == "no_token" || err == "token_invalid") {
			getToken();
			return true;
		}

		// TODO: move this to windows
//		if (err == "no_access") {
//			mess = QObject::tr("Недостаточно прав для этого действия");
//
//		} else
		if (err == "invalid_credentials") {
			mess = QObject::tr("Неправильный логин/пароль");

		} else if (err == "could_not_create_token") {
			mess = QObject::tr("Внутренняя ошибка сервера") + '\n' +
			       QObject::tr("Обратитесь к администратору с фотографией ошибки") + '\n' +
			       o["message"].toString();

		}

		QMessageBox::critical(0, QObject::tr(""), mess);
		return true;
	}

	return false;
}

void TDB::refreshToken() {
	QJsonObject o = GET("auth/ref", {{"token", token}});

	if (!hasErrors(o)) {
		token = o["token"].toString();
		conf.set("token", token);
	}
}

QStringList TDB::getRoles() {
	QStringList r;

	QJsonObject o = request("auth/roles");
	for (QJsonValue v : o["roles"].toArray())
		r << v.toString();

	return r;
}


