#ifndef SCANRULE_HPP
#define SCANRULE_HPP

#include "validator.hpp"
#include <QRegularExpression>
#include <memory>
#include <vector>
#include <QVector>

class ScanRule {
private:
    std::vector<std::shared_ptr<Validator> > validators_;
    QRegularExpression pattern_;
    ScanType type_;

public:
    ScanRule(QString pattern, ScanType type);

    inline void addValidator(std::shared_ptr<Validator> validator) { validators_.push_back(std::move(validator)); }

    QVector<ScanResult> apply(QString data) const;
};

#endif // SCANRULE_HPP
