#include "documentparser.h"

DocumentParser::DocumentParser()
{

}

void DocumentParser::readFile(const QString &path)
{
    /* Read File */
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error while loading file";
    }

    document.setContent(&file);

    /* First Parametr */
    QDomElement root = document.documentElement();

    /* Data Access */
    QDomElement Component = root.firstChild().toElement();

    /* Check Elements */
    while(!Component.isNull()) {

        /* Component Name */
        if (Component.tagName() == "entry") {

            // Get the first child of the component
            QDomElement Child = Component.firstChild().toElement();

            QString Title;
            QString VideoID;
            QString Link;

            /* Read each child of the component */
            while (!Child.isNull()) {

                /* Read Parameters */
                if (Child.tagName() == "title")         Title = Child.firstChild().toText().data();
                if (Child.tagName() == "yt:videoId")    VideoID = Child.firstChild().toText().data();
                if (Child.tagName() == "link")          Link = Child.attribute("href");

                /* Next Child */
                Child = Child.nextSibling().toElement();
            }

            /* Show Data */
            qDebug() << "Title:" << Title;
            qDebug() << "VideoID:" << VideoID;
            qDebug() << "Link:" << Link;
            xmlData.push_back(XMLData(Title, VideoID, Link));
        }

        /* Next Component */
        Component = Component.nextSibling().toElement();
    }

    file.close();
}

QVector<XMLData> DocumentParser::getXmlData() const
{
    return xmlData;
}












