#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

class NetworkManager {
private:
    QNetworkAccessManager manager;
    QNetworkReply *response;
    QEventLoop event;
    QString html;

public:
    NetworkManager();
    int setURLName(const QString &name);
    QString getURLContent() const;
};

#endif // NETWORKMANAGER_H
