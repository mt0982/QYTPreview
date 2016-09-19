#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QDir>
#include <QTextStream>
#include <QPixmap>
#include <imagenetworkmanager.h>

class XMLData {
private:
    ImageNetworkManager *imageManager;

public:
    QString title;
    QString videoID;
    QString link;
    QPixmap image;

    XMLData(){}
    XMLData(QString t, QString v, QString l, QString imageURL): title(t), videoID(v), link(l) {
        imageManager = new ImageNetworkManager;
        imageManager->processingURLImage(imageURL);
    }
};

class DocumentParser {
private:
    QDomDocument document;
    QVector<XMLData> xmlData;

public:
    DocumentParser();
    void readFile(const QString &path);
    QVector<XMLData> getXmlData() const;
};

#endif // DOCUMENTPARSER_H
