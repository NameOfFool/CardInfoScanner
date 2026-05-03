#include "include/backend.hpp"
#include <QDirIterator>
#include <QUrl>
#include <QDebug>

#include "include/image_scanner_parser.hpp"
#include "include/luhna_validator.hpp"
#include "include/scanner_engine.hpp"
#include "include/text_scanner_parser.hpp"

Backend::Backend(QObject *parent)
    : QObject(parent) {
    ScanRule rule{R"(\b\d{4}[- ]?\d{4}[- ]?\d{4}[- ]?\d{4}\b)", ScanType::PAM};
    rule.addValidator(std::make_shared<LuhnaValidator>());
    scannerEngine.addRule(rule);
    parsers[".txt"] = std::make_unique<TextScannerParser>();
    parsers[".png"] = std::make_unique<ImageScannerParser>();
}

void Backend::processChunk(const QString &text, const QString &name) const {
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
        const auto fileType = getFileType(file);
        if (!file.open(QIODevice::ReadOnly) || !fileType.contains(filesType) || parsers.find(fileType) == parsers.
            end()) {
            qDebug() << "Skipping" << filePath;
            continue;
        }
        const auto parser = parsers.at(fileType);

        qDebug() << "Reading:" << file.fileName();
        file.close();

        parser->parseFile(filePath, [this](auto text, auto name) {
            return processChunk(text, name);
        });
    }
    qDebug() << "Finished";
    emit scanningFinished();
}

QString Backend::getFileType(const QFile &file) {
    const QFileInfo fileInfo(file.fileName());
    return "." + fileInfo.suffix();
}
