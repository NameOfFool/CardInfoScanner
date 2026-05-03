
#ifndef CARDSEARCHER_TEXT_SCANNER_PARSER_HPP
#define CARDSEARCHER_TEXT_SCANNER_PARSER_HPP
#include <qfile.h>

#include "iscanner_parser.hpp"


class TextScannerParser : public IScannerParser {
public:
    void parseFile(const QString &filePath, std::function<void(const QString &, const QString &)> onParsed) override {
        // 64 KB
        QFile file(filePath);
        constexpr qint64 chunkSize = 64 * 1024;
        while (!file.atEnd()) {
            QByteArray buffer = file.read(chunkSize);
            // Здесь анализ чанка
            onParsed(QString::fromUtf8(buffer), filePath);
        }
    }
};


#endif //CARDSEARCHER_TEXT_SCANNER_PARSER_HPP
