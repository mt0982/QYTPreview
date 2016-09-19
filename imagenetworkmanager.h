#ifndef IMAGENETWORKMANAGER_H
#define IMAGENETWORKMANAGER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <documentparser.h>

class ImageNetworkManager: public QObject {
    Q_OBJECT

public:
    ImageNetworkManager();
    void setContainer(QVector<XMLData> &container);
    void processingURLImage(const QString &link);

private slots:
    void mFinish(QNetworkReply *reply);

private:
    int counter;
    QPixmap pixmap;
    QNetworkAccessManager *networkManager;
    QVector<XMLData> xmlData;
};

#endif // IMAGENETWORKMANAGER_H
