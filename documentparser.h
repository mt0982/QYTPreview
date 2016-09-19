#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QDebug>
#include <QFile>
#include <QDomDocument>

class DocumentParser {
private:
    QDomDocument document;

public:
    DocumentParser();
    void readFile(const QString &path);
};

#endif // DOCUMENTPARSER_H
