//
// Created by fool on 24.04.2026.
//

#include "../include/backend.hpp"


#include <QDirIterator>
#include <QUrl>
#include <QDebug>

#include "include/luhna_validator.hpp"
#include "include/scanner_engine.hpp"

Backend::Backend(QObject *parent)
    : QObject(parent), scannerEngine() {
    ScanRule rule{R"(\b\d{4}[- ]?\d{4}[- ]?\d{4}[- ]?\d{4}\b)", ScanType::PAM};
    rule.addValidator(std::make_shared<LuhnaValidator>());
    scannerEngine.addRule(rule);
}

void Backend::processChunk(const QByteArray &data) {
    QString text = QString::fromUtf8(data);

    auto result = scannerEngine.scan(text);

    for (const auto& r : result) {
        qDebug() << r.match;
    }
}

void Backend::processFolder(const QString &folderUrl) {
    // Парсинг file:///
    QString path = QUrl(folderUrl).toLocalFile();

    qDebug() << "Scanning:" << path;

    QDirIterator it(path,
                    QDir::Files,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filePath = it.next();

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly) || !file.fileName().contains("example.txt")) {
            continue;
        }

        qDebug() << "Reading:" << file.fileName();

        // 64 KB
        const qint64 chunkSize = 64 * 1024;
        QByteArray buffer;

        while (!file.atEnd()) {
            buffer = file.read(chunkSize);

            // Здесь анализ чанка
            processChunk(buffer);
        }
    }
    qDebug() << "Finished";
}
