#include "jsonreader.h"

JsonReader::JsonReader(const QString &filePath)
    : filePath(filePath) {}

bool JsonReader::isValid() const {
    QFile file(filePath);
    return file.exists();
}

double JsonReader::readTotalSum() {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open JSON file!";
        return 0.0;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "Invalid JSON format!";
        return 0.0;
    }

    QJsonArray arr = doc.array();
    double totalSum = 0.0;

    for (const QJsonValue &value : arr) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            double total = obj.value("total").toDouble();
            totalSum += total;
        }
    }
    return totalSum;
}
