#include "documentparser.h"

DocumentParser::DocumentParser()
{

}

void DocumentParser::readFile(const QString &path)
{
    /* Clear Data Container */
    xmlData.clear();

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
            QString ImageURL;

            /* Read each child of the component */
            while (!Child.isNull()) {

                /* Read Parameters */
                if (Child.tagName() == "title")         Title = Child.firstChild().toText().data();
                if (Child.tagName() == "yt:videoId")    VideoID = Child.firstChild().toText().data();
                if (Child.tagName() == "link")          Link = Child.attribute("href");
                if (Child.tagName() == "media:group") {

                    /* Fine Next Child (Image URL) */
                    QDomElement nextChild = Child.firstChild().toElement();
                    while(!nextChild.isNull()) {
                        if(nextChild.tagName() == "media:thumbnail"){
                            ImageURL = nextChild.attribute("url");
                        }
                        nextChild = nextChild.nextSibling().toElement();
                    }
                }

                /* Next Child */
                Child = Child.nextSibling().toElement();
            }

            /* Show Data */
            qDebug() << "Title:" << Title;
            qDebug() << "VideoID:" << VideoID;
            qDebug() << "Link:" << Link;
            qDebug() << "ImageURL:" << ImageURL;
            xmlData.push_back(XMLData(Title, VideoID, Link, ImageURL));
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












