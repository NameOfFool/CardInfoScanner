#ifndef CARDSEARCHER_SCANNER_PARSER_HPP
#define CARDSEARCHER_SCANNER_PARSER_HPP
#include <QString>

class IScannerParser {
public:
    virtual void parseFile(const QString &filePath, std::function<void(const QString &, const QString &)> onParsed) = 0;

    virtual ~IScannerParser() = default;
};

#endif //CARDSEARCHER_SCANNER_PARSER_HPP
