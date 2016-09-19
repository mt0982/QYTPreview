#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QDebug>
#include <QFile>
#include <QDomDocument>

class XMLData {
public:
    QString title;
    QString videoID;
    QString link;
    XMLData(){}
    XMLData(QString t, QString v, QString l): title(t), videoID(v), link(l){}
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
