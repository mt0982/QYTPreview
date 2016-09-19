#include "networkmanager.h"

NetworkManager::NetworkManager()
{

}

int NetworkManager::setURLName(const QString &name)
{
    response = manager.get(QNetworkRequest(QUrl("https://www.youtube.com/feeds/videos.xml?user=" + name)));
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();

    html = response->readAll();
    qDebug() << "File Size:" << html.size();
    return html.size();
}

QString NetworkManager::getURLContent() const
{
    return html;
}
