#ifndef CARDSEARCHER_BACKEND_HPP
#define CARDSEARCHER_BACKEND_HPP
#include <QFile>

#include "iscanner_parser.hpp"
#include "scanner_engine.hpp"

class Backend : public QObject {
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE void processFolder(const QString &folderUrl, const QString &filesType);

signals:
    void scanningFinished();

private:
    ScannerEngine scannerEngine;

    void processChunk(const QString &text, const QString &name) const;

    QString getFileType(const QFile &file);

    std::unordered_map<QString, std::shared_ptr<IScannerParser>> parsers;
};


#endif //CARDSEARCHER_BACKEND_HPP
