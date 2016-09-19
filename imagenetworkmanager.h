#ifndef IMAGENETWORKMANAGER_H
#define IMAGENETWORKMANAGER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

class ImageNetworkManager: public QObject {
    Q_OBJECT

public:
    ImageNetworkManager();
    void processingURLImage(const QString &link);
    QPixmap getImage() const;

private slots:
    void mFinish(QNetworkReply *reply);

private:
    QPixmap pixmap;
    QNetworkAccessManager *networkManager;
};

#endif // IMAGENETWORKMANAGER_H
