//
// Created by fool on 24.04.2026.
//

#ifndef CARDSEARCHER_BACKEND_HPP
#define CARDSEARCHER_BACKEND_HPP


#include <QObject>

#include "scanner_engine.hpp"

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(QObject* parent = nullptr);

    Q_INVOKABLE void processFolder(const QString& folderUrl);

private:
    ScannerEngine scannerEngine;

    void processChunk(const QByteArray &data);
};


#endif //CARDSEARCHER_BACKEND_HPP
