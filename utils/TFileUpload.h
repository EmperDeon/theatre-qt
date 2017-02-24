#ifndef THEATRE_ADMIN_TFILEUPLOAD_H
#define THEATRE_ADMIN_TFILEUPLOAD_H

#include <QtWidgets>

class TFileUpload : public QWidget {
	QLabel *l_img;
	QString url;

public:
	TFileUpload(QString u = "no_img");

	void upload();

	QString getUrl() const;

	void load(QString u);

	void clear();

	static QPixmap getPreview(QString u);

	static QPixmap getImage(QJsonValue p);
};


#endif //THEATRE_ADMIN_TFILEUPLOAD_H
