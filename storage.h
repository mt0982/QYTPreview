#ifndef STORAGE_H
#define STORAGE_H

#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QVector>
#include <QDebug>

class Storage {
public:
    Storage();
    void save(QVector<QString> &channel);
    QVector<QString> load();
};

#endif // STORAGE_H
