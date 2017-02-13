#ifndef THEATRE_ADMIN_TFILEUPLOAD_H
#define THEATRE_ADMIN_TFILEUPLOAD_H

#include <QtWidgets>

class TFileUpload : public QWidget {
	QLabel *l_img;
	QString url;

public:
	TFileUpload(QString u = "none");

	void upload();

	QString getUrl() const { return url; }

	void load(QString u);

	static QPixmap getPreview(QString u);

	static QPixmap getImage(QJsonValue p);
};


#endif //THEATRE_ADMIN_TFILEUPLOAD_H
