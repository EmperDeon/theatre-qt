#include "THallPreview.h"
#include "utils/TFileUpload.h"

THallPreview::THallPreview(QJsonObject o) : TTModel(o) {
	QLabel *l = new QLabel();
	l->setPixmap(TFileUpload::getImage(o["preview"]));
	layout->addWidget(l);
}

QString THallPreview::getPath() {
	return "t_halls";
}

void THallPreview::setFEnabled(bool b) {

}

QMap<QString, QString> THallPreview::getParams() {
	return {};
}
