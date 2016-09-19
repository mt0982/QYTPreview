#include "imagenetworkmanager.h"

ImageNetworkManager::ImageNetworkManager(): counter(0)
{

}

void ImageNetworkManager::setContainer(QVector<XMLData> &container)
{
    counter = 0;
    xmlData = container;
    for(int i = 0; i < xmlData.size(); i++) {
        processingURLImage(xmlData[i].imageURL);
    }

    /* Back Data To Main Thread */
    container = xmlData;
}

void ImageNetworkManager::processingURLImage(const QString &link)
{
    networkManager = new QNetworkAccessManager();
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(mFinish(QNetworkReply*)));

    QUrl url(link);
    QNetworkRequest request(url);
    networkManager->get(request);

    /* Synchronous Wait */
    QEventLoop loop;
    loop.connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
    loop.exec();
}

void ImageNetworkManager::mFinish(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        return;
    }

    QByteArray jpegData = reply->readAll();
    pixmap.loadFromData(jpegData);

    xmlData[counter].image = pixmap;
    qDebug() << "Finished - Image Loaded:" << xmlData[counter].image.size();
    counter++;
}





















