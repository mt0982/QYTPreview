#include "imagenetworkmanager.h"

ImageNetworkManager::ImageNetworkManager()
{

}

void ImageNetworkManager::processingURLImage(const QString &link)
{
    networkManager = new QNetworkAccessManager();
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(mFinish(QNetworkReply*)));

    QUrl url(link);
    QNetworkRequest request(url);
    networkManager->get(request);
}

QPixmap ImageNetworkManager::getImage() const
{
    return pixmap;
}

void ImageNetworkManager::mFinish(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        return;
    }

    QByteArray jpegData = reply->readAll();
    pixmap.loadFromData(jpegData);
    qDebug() << "Finished:" << pixmap.size();
}





















