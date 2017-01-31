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

QJsonValue TDB::request(QString path, QMap<QString, QString> params) {
	qDebug() << "Request:" << path << ", params:" << params;

//	if (params.contains("desc")) {
//		QString desc = params["desc"];
//		desc = desc.replace('\n', "<br>");
//		params["desc"] = desc;
//	}
//	if (params.contains("desc_s")) {
//		QString desc = params["desc_s"];
//		desc = desc.replace('\n', "<br>");
//		params["desc_s"] = desc;
//	}

	checkAndRefreshToken();
	params.insert("token", token);

	QString r_type;
	if (path.endsWith("/create") || path.endsWith("/update") || path.endsWith("/destroy") ||
	    path.endsWith("/restore") || path == "auth_api/perms")
		r_type = "POST";
	else
		r_type = "GET";

	QJsonValue r = GET(path, params, r_type);
	hasErrors();

	writeToLog(path, params, r_type);

	return r;
}

QJsonValue TDB::GET(QString path, QMap<QString, QString> params, QString r_type) {
	QTime requestTime;
	requestTime.start();

//	QUrl c("https://api-theatre.herokuapp.com/" + path);
	QUrl c("http://127.0.0.1:3000/" + path);

	QUrlQuery q; // Query items
	for (QString k : params.keys())
		q.addQueryItem(k, params[k]);


	QNetworkRequest req;
	QNetworkReply *rep;

	if (r_type == "GET") {
		c.setQuery(q);

		req.setUrl(c);
		rep = manager.get(req);

	} else if (r_type == "POST") {
		req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

		req.setUrl(c);
		rep = manager.post(req, q.toString(QUrl::FullyEncoded).toUtf8());

	} else {
		qDebug() << "Something wrong, r_type = " << r_type;
		return QJsonValue();
	}

//	qDebug() << c << q.toString();

	QEventLoop wait;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(60000, &wait, SLOT(quit()));
	wait.exec();

	lastReply = QJsonDocument::fromJson(rep->readAll()).object();
	lastError = rep->error();
	lastTime = requestTime.elapsed();

	rep->deleteLater();

	return lastReply["response"];
}

void TDB::getToken() {
	QJsonObject cred = TDLogin::getCredentials();
	if (cred.isEmpty()) {
		exit(0); // TODO: prettify

	} else {
		conf.set("login", cred["login"]);

		QJsonObject o = GET("auth_api/new", QMap<QString, QString>{
				{"login", cred["login"].toString()},
				{"pass",  cred["password"].toString()}
		}, "POST").toObject();
		qDebug() << o;
		if (hasErrors()) {
			getToken();

		} else {
			token = o["auth_token"].toString();
			conf.set("token", token);

		}
	}

	conf.save();
}

void TDB::checkAndRefreshToken() {
	GET("auth_api/check", {{"token", token}}, "POST").toString();

	if (hasErrors()) {
		checkAndRefreshToken();

	}
}

bool TDB::hasErrors() {
	if (lastReply.contains("error")) {
		QString err = lastReply["error"].toString(), mess;

		if (lastReply.contains("exception")) {
			qDebug() << "Error: " << err << lastReply["exception"].toString();

			QMessageBox::critical(0, err, mess = QObject::tr("Внутренняя ошибка сервера") + '\n' +
			                                     QObject::tr("Обратитесь к администратору с фотографией ошибки") +
			                                     '\n' +
			                                     lastReply["exception"].toString());
			return true;

		} else {
			qDebug() << "Error:" << err;


			if (err == "no_token" || err == "token_invalid") {
				getToken();
				return true;
			}

			if (err == "no_access") {
				err = "Ошибка";
				mess = QObject::tr("Недостаточно прав для этого действия");

			} else if (err == "invalid_credentials") {
				mess = QObject::tr("Неправильный логин/пароль");

			} else if (err == "no_id") {
				err = "Ошибка";
				mess = "Строки с таким id не существует";

			} else if (err == "entry_exists") {
				err = "Ошибка";
				mess = "Такая запись уже существует";

			} else if (err == "no_def_value") {
				err = "Ошибка";
				mess = "Введены не все данные";

			} else if (err == "could_not_create_token") {
				mess = QObject::tr("Внутренняя ошибка сервера") + '\n' +
				       QObject::tr("Обратитесь к администратору с фотографией ошибки") + '\n' +
				       lastReply["message"].toString();

			}

			QMessageBox::critical(0, err, mess);
			return true;
		}
	}

	return false;
}

QStringList TDB::getPerms() {
	QStringList r;

	QJsonArray o = request("auth_api/perms").toArray();
	for (QJsonValue v : o)
		r << v.toString();

	return r;
}

void TDB::writeToLog(QString path, QMap<QString, QString> params, QString r_type) {
	QJsonObject o;

	o["path"] = path;
	o["r_type"] = r_type;

	o["response"] = lastReply;
	o["code"] = getResponseCode();
	o["time"] = lastTime;

	QJsonObject t;
	for (QString k : params.keys()) {
		if (k != "token")
			t[k] = params[k];
	}
	o["params"] = t;

	// Save
}

QString TDB::getResponseCode() const {
	switch (lastError) {
		case QNetworkReply::NoError:
			return "200 OK";
		case QNetworkReply::ConnectionRefusedError:
		case QNetworkReply::RemoteHostClosedError:
		case QNetworkReply::HostNotFoundError:
		case QNetworkReply::TimeoutError:
		case QNetworkReply::OperationCanceledError:
		case QNetworkReply::SslHandshakeFailedError:
		case QNetworkReply::TemporaryNetworkFailureError:
		case QNetworkReply::NetworkSessionFailedError:
		case QNetworkReply::BackgroundRequestNotAllowedError:
		case QNetworkReply::TooManyRedirectsError:
		case QNetworkReply::InsecureRedirectError:
		case QNetworkReply::UnknownNetworkError:
		case QNetworkReply::ProxyConnectionRefusedError:
		case QNetworkReply::ProxyConnectionClosedError:
		case QNetworkReply::ProxyNotFoundError:
		case QNetworkReply::ProxyTimeoutError:
		case QNetworkReply::ProxyAuthenticationRequiredError:
		case QNetworkReply::UnknownProxyError:
		case QNetworkReply::ContentAccessDenied:
		case QNetworkReply::ContentOperationNotPermittedError:
		case QNetworkReply::ContentNotFoundError:
			return "404";
		case QNetworkReply::AuthenticationRequiredError:
			return "401";
		case QNetworkReply::ContentReSendError:
		case QNetworkReply::ContentConflictError:
		case QNetworkReply::ContentGoneError:
		case QNetworkReply::UnknownContentError:
		case QNetworkReply::ProtocolUnknownError:
		case QNetworkReply::ProtocolInvalidOperationError:
		case QNetworkReply::ProtocolFailure:
		case QNetworkReply::InternalServerError:
			return "500";
		case QNetworkReply::OperationNotImplementedError:
			return "501";
		case QNetworkReply::ServiceUnavailableError:
			return "503";
		case QNetworkReply::UnknownServerError:

		default:
			return "";
	}


//	HTTP_STATUS_CODES = {
//			100 => 'Continue',
//			101 => 'Switching Protocols',
//			102 => 'Processing',

//			200 => 'OK',
//			201 => 'Created',
//			202 => 'Accepted',
//			203 => 'Non-Authoritative Information',
//			204 => 'No Content',
//			205 => 'Reset Content',
//			206 => 'Partial Content',

}


