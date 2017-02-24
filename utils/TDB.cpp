#include "TDB.h"
#include <QtWidgets>
#include <windows/TMainWindow.h>
#include "dialogs/TDLogin.h"


QJsonValue TDB::request(QString path, QMap<QString, QString> params) {
	// Join all parameters to string
	QString keys = params.keys().join(", ");

	checkAndRefreshToken();
	params.insert("token", TConfig::getS("token"));

	QString r_type;
	if (
			path.endsWith("/create") ||
			path.endsWith("/update") ||
			path.endsWith("/destroy") ||
			path.endsWith("/restore") ||
			path.startsWith("auth_api")
			) {
		r_type = "POST";
	} else {
		r_type = "GET";
	}

	QJsonValue r = GET(path, params, r_type);

	qDebug() << QString("[ %1] '%2'  params: '%3'")
			.arg(r_type, 4).arg(path, 22).arg(keys)
			.toStdString().c_str();

	hasErrors();

	TMainWindow *main_w = TMainWindow::getInstance();
	main_w->showStatusMessage(getCodeDesc(path));

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
		TConfig::set("login", cred["login"]);

		QJsonObject o = GET("auth_api/new", QMap<QString, QString>{
				{"login", cred["login"].toString()},
				{"pass",  cred["password"].toString()}
		}, "POST").toObject();

		if (hasErrors()) {
			getToken();

		} else {
			QString token = o["auth_token"].toString();
			TConfig::set("token", token);

		}
	}
}

void TDB::checkAndRefreshToken() {
	GET("auth_api/check", {{"token", TConfig::getS("token")}}, "POST").toString();

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

	TConfig::set("lastPerms", o);

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
	QJsonArray a;
	QFile f("log.json");
	if (f.open(QFile::ReadOnly)) {
		a = QJsonDocument::fromJson(f.readAll()).array();
		f.close();
	}

	a << o;

	f.open(QFile::WriteOnly);
	f.write(QJsonDocument(a).toJson());
	f.close();
}

QString TDB::getResponseCode() const {
	switch (lastError) {
		case QNetworkReply::NoError:
			return "200";
		case QNetworkReply::AuthenticationRequiredError:
			return "401";
		case QNetworkReply::ContentNotFoundError:
			return "404";
		case QNetworkReply::ContentOperationNotPermittedError:
			return "403";
		case QNetworkReply::UnknownContentError:
			return "422";
		case QNetworkReply::InternalServerError:
			return "500";

//		case QNetworkReply::NoError:                           return "200 OK";
//		case QNetworkReply::AuthenticationRequiredError:       return "401 Auth required";
//		case QNetworkReply::ContentNotFoundError:              return "404 Not found";
//		case QNetworkReply::ContentOperationNotPermittedError: return "403 || 405 Not permitted";
//		case QNetworkReply::UnknownContentError:               return "422 Validation error";
//		case QNetworkReply::InternalServerError:               return "500 Internal error";

		case QNetworkReply::ProxyAuthenticationRequiredError:
			return "407";
		case QNetworkReply::ContentConflictError:
			return "409";
		case QNetworkReply::ContentGoneError:
			return "410";
		case QNetworkReply::ProtocolInvalidOperationError:
			return "400";
		case QNetworkReply::OperationNotImplementedError:
			return "501";
		case QNetworkReply::ServiceUnavailableError:
			return "503";
		case QNetworkReply::UnknownServerError:
			return "502 .. 511";

		case QNetworkReply::HostNotFoundError:
			return "Error No host";
		case QNetworkReply::ConnectionRefusedError:
			return "Error ConnectionRefused";
		case QNetworkReply::RemoteHostClosedError:
			return "Error RemoteHostClosed";
		case QNetworkReply::TimeoutError:
			return "Error Timeout";
		case QNetworkReply::OperationCanceledError:
			return "Error OperationCanceled";
		case QNetworkReply::SslHandshakeFailedError:
			return "Error SslHandshakeFailed";
		case QNetworkReply::TemporaryNetworkFailureError:
			return "Error TemporaryNetworkFailure";
		case QNetworkReply::NetworkSessionFailedError:
			return "Error NetworkSessionFailed";
		case QNetworkReply::BackgroundRequestNotAllowedError:
			return "Error BackgroundRequestNotAllowed";
		case QNetworkReply::TooManyRedirectsError:
			return "Error TooManyRedirects";
		case QNetworkReply::InsecureRedirectError:
			return "Error InsecureRedirect";
		case QNetworkReply::UnknownNetworkError:
			return "Error UnknownNetwork";
		case QNetworkReply::ProxyConnectionRefusedError:
			return "Error ProxyConnectionRefused";
		case QNetworkReply::ProxyConnectionClosedError:
			return "Error ProxyConnectionClosed";
		case QNetworkReply::ProxyNotFoundError:
			return "Error ProxyNotFound";
		case QNetworkReply::ProxyTimeoutError:
			return "Error ProxyTimeout";
		case QNetworkReply::UnknownProxyError:
			return "Error UnknownProxy";
		case QNetworkReply::ContentAccessDenied:
			return "Error ContentAccessDenied";
		case QNetworkReply::ContentReSendError:
			return "Error ContentReSend";
		case QNetworkReply::ProtocolUnknownError:
			return "Error ProtocolUnknown";
		case QNetworkReply::ProtocolFailure:
			return "Error ProtocolFailure";

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

QString TDB::getCodeDesc(QString path) {
	switch (lastError) {
		case QNetworkReply::NoError: {
			QString r = "Успешно ";
			if (path.endsWith("create")) {
				r += "создано";

			} else if (path.endsWith("update")) {
				r += "изменено";

			} else if (path.endsWith("destroy")) {
				r += "удалено";

			} else if (path.endsWith("restore")) {
				r += "восстановлено";

			} else {
				return "Успешное другое действие";
			}
			return r;
		}

		case QNetworkReply::AuthenticationRequiredError:
			return "Ошибка авторизации";
		case QNetworkReply::ContentNotFoundError:
			return "Элемент не найден";
		case QNetworkReply::ContentOperationNotPermittedError:
			return "Недостаточно прав для совершения действия";
		case QNetworkReply::UnknownContentError:
			return "?Ошибка валидации?";
		case QNetworkReply::InternalServerError:
			return "Внутренняя ошибка сервера, обратитесь к администратору";

//		case QNetworkReply::NoError:                           return "200 OK";
//		case QNetworkReply::AuthenticationRequiredError:       return "401 Auth required";
//		case QNetworkReply::ContentNotFoundError:              return "404 Not found";
//		case QNetworkReply::ContentOperationNotPermittedError: return "403 || 405 Not permitted";
//		case QNetworkReply::UnknownContentError:               return "422 Validation error";
//		case QNetworkReply::InternalServerError:               return "500 Internal error";

		case QNetworkReply::ProxyAuthenticationRequiredError:
			return "407";
		case QNetworkReply::ContentConflictError:
			return "409";
		case QNetworkReply::ContentGoneError:
			return "410";
		case QNetworkReply::ProtocolInvalidOperationError:
			return "400";
		case QNetworkReply::OperationNotImplementedError:
			return "501";
		case QNetworkReply::ServiceUnavailableError:
			return "503";
		case QNetworkReply::UnknownServerError:
			return "502 .. 511";

		case QNetworkReply::HostNotFoundError:
			return "Ошибка подключения к серверу";
		case QNetworkReply::ConnectionRefusedError:
			return "Error ConnectionRefused";
		case QNetworkReply::RemoteHostClosedError:
			return "Error RemoteHostClosed";
		case QNetworkReply::TimeoutError:
			return "Error Timeout";
		case QNetworkReply::OperationCanceledError:
			return "Error OperationCanceled";
		case QNetworkReply::SslHandshakeFailedError:
			return "Error SslHandshakeFailed";
		case QNetworkReply::TemporaryNetworkFailureError:
			return "Error TemporaryNetworkFailure";
		case QNetworkReply::NetworkSessionFailedError:
			return "Error NetworkSessionFailed";
		case QNetworkReply::BackgroundRequestNotAllowedError:
			return "Error BackgroundRequestNotAllowed";
		case QNetworkReply::TooManyRedirectsError:
			return "Error TooManyRedirects";
		case QNetworkReply::InsecureRedirectError:
			return "Error InsecureRedirect";
		case QNetworkReply::UnknownNetworkError:
			return "Error UnknownNetwork";
		case QNetworkReply::ProxyConnectionRefusedError:
			return "Error ProxyConnectionRefused";
		case QNetworkReply::ProxyConnectionClosedError:
			return "Error ProxyConnectionClosed";
		case QNetworkReply::ProxyNotFoundError:
			return "Error ProxyNotFound";
		case QNetworkReply::ProxyTimeoutError:
			return "Error ProxyTimeout";
		case QNetworkReply::UnknownProxyError:
			return "Error UnknownProxy";
		case QNetworkReply::ContentAccessDenied:
			return "Error ContentAccessDenied";
		case QNetworkReply::ContentReSendError:
			return "Error ContentReSend";
		case QNetworkReply::ProtocolUnknownError:
			return "Error ProtocolUnknown";
		case QNetworkReply::ProtocolFailure:
			return "Error ProtocolFailure";

		default:
			return "";
	}
}

QJsonValue TDB::uploadFiles(QMap<QString, QString> files, QMap<QString, QString> params) {
	QMap<QString, QIODevice *> io;

	for (QString k : files.keys()) {
		QFile *f = new QFile(files[k]);
		f->open(QIODevice::ReadOnly);

		io[k] = f;
	}

	return upload(io, params);
}

QJsonValue TDB::upload(QMap<QString, QIODevice *> io, QMap<QString, QString> params) {
//	QUrl c("https://api-theatre.herokuapp.com/utils/upload");
	QUrl c("http://127.0.0.1:3000/utils/upload");

	QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	for (QString k : io.keys()) {
		appendFilePart(multipart, k, io[k]);
	}

	for (QString k : params.keys()) {
		appendStringPart(multipart, k, params[k]);
	}

	QNetworkRequest request(c);
	QNetworkReply *rep = manager.post(request, multipart);
	multipart->setParent(rep);

	QEventLoop wait;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(60000, &wait, SLOT(quit()));
	wait.exec();

	lastReply = QJsonDocument::fromJson(rep->readAll()).object();
	lastError = rep->error();

	qDebug() << QString("[ %1] '%2'  params: '%3'")
			.arg("POST", 4).arg("utils/upload", 18).arg((io.keys() + params.keys()).join(", "))
			.toStdString().c_str();

	hasErrors();

	return lastReply["response"];
}

void TDB::appendFilePart(QHttpMultiPart *multipart, QString k, QIODevice *v) const {
	QHttpPart file_part;

	file_part.setHeader(QNetworkRequest::ContentDispositionHeader,
	                    "form-data; name=\"" + k + "\"; filename=\"" + k + "\"");
	file_part.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");

	file_part.setBodyDevice(v);
	v->setParent(multipart);

	multipart->append(file_part);
}

void TDB::appendStringPart(QHttpMultiPart *multipart, QString k, QString v) const {
	QHttpPart r;

	r.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"" + k + "\"");
	r.setBody(v.toUtf8());

	multipart->append(r);
}


