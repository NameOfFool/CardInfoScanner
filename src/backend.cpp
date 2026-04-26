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

void Backend::processChunk(const QByteArray &data, const QString& name) {
    const QString text = QString::fromUtf8(data);

    auto result = scannerEngine.scan(text);
    QFile file("output.txt");
    for (const auto &r: result) {
        qDebug() << r.match;

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << name << ": " << r.match << Qt::endl;

        }
    }
    file.close();
}

void Backend::processFolder(const QString &folderUrl, const QString &filesType) {
    // Парсинг file:///
    const QString path = QUrl(folderUrl).toLocalFile();

    qDebug() << "Scanning:" << path << ", searching for " << filesType;

    QDirIterator it(path,
                    QDir::Files,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filePath = it.next();

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly) || !file.fileName().contains(filesType)) {
            continue;
        }

        qDebug() << "Reading:" << file.fileName();

        // 64 KB
        const qint64 chunkSize = 64 * 1024;
        QByteArray buffer;

        while (!file.atEnd()) {
            buffer = file.read(chunkSize);

            // Здесь анализ чанка
            processChunk(buffer, filePath);
        }
    }
    qDebug() << "Finished";
}
