#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QDir>
#include <QTextStream>
#include <QPixmap>

class XMLData {
public:
    QString title;
    QString videoID;
    QString link;
    QPixmap image;
    QString imageURL;

    XMLData(){}
    XMLData(QString t, QString v, QString l, QString url): title(t), videoID(v), link(l), imageURL(url){}
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











