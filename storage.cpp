#include "storage.h"

Storage::Storage()
{

}

void Storage::save(QVector<QString> &channel)
{
    QFile file(QDir::currentPath() + "storage");
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Storage Save Error";
    }

    QDataStream out(&file);
    out << channel;
    qDebug() << "Data saved";
}

QVector<QString> Storage::load()
{
    QFile file(QDir::currentPath() + "storage");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Storage Load Error";
    }

    QDataStream in(&file);
    QVector<QString> channel;
    in >> channel;

    foreach (QString x, channel) {
        qDebug() << "Loaded:" << x;
    }

    return channel;
}


























