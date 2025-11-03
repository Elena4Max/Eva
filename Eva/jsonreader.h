#ifndef JSONREADER_H
#define JSONREADER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

class JsonReader {
public:
    explicit JsonReader(const QString &filePath);
    double readTotalSum();
    bool isValid() const;

private:
    QString filePath;
    QString errorString;
};

#endif // JSONREADER_H
