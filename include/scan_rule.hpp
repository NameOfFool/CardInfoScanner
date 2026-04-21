#ifndef SCANRULE_HPP
#define SCANRULE_HPP

#include "validator.hpp"
#include <QRegularExpression>
#include <memory>
#include <vector>

class ScanRule {
  private:
    std::vector<std::unique_ptr<Validator>> validators_;
    QRegularExpression pattern_;
    ScanType type_;

  public:
    ScanRule(QString pattern, ScanType type);
    inline void addValidator(std::unique_ptr<Validator> validator) { validators_.push_back(std::move(validator)); }
    std::vector<ScanResult> apply(QString data) const;
};

#endif // SCANRULE_HPP
