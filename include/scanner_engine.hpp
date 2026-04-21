#ifndef SCANNER_ENGINE_HPP
#define SCANNER_ENGINE_HPP

#include "scan_rule.hpp"
#include <QString>
#include <QVector>

class ScannerEngine {
  public:
    void addRule(const ScanRule& rule) { rules_.push_back(std::move(rule)); }

    QVector<ScanResult> scan(const QString& data) const
    {
        QVector<ScanResult> allResults;

        for(const auto& rule : rules_) {
            auto results = rule.apply(data);
            allResults.append(results);
        }

        return allResults;
    }

  private:
    QVector<ScanRule> rules_;
};

#endif // SCANNER_ENGINE_HPP
