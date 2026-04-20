#ifndef SCANRESULT_HPP
#define SCANRESULT_HPP

#include <QString>
#include <QVector>
#include <cstddef>

// Структура контекста поиска. Содержит текст, где найдено совпадение, позицию и длину совпадения
struct Context {
    QString fullData;
    qsizetype position;
    qsizetype length;
};

// Определяет тип результата сканирования
enum class ScanType { PAM, CVV, Expiry };

// Структура с результатом сканирования по правилам ScanRule
struct ScanResult {
    QString match;
    qsizetype offset;
    ScanType type;

    double confidence;

    // важно для explainability
    QVector<QString> sigs;
};

#endif // SCANRESULT_HPP
