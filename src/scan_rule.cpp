#include "../include/scan_rule.hpp"
#include "../include/scan_result.hpp"

ScanRule::ScanRule(QString pattern, ScanType type) : pattern_(std::move(pattern)), type_(type) {}

std::vector<ScanResult> ScanRule::apply(QString data) const
{
    std::vector<ScanResult> results;

    for(const QRegularExpressionMatch& match : pattern_.globalMatch(data)) {
        Context ctx{data, match.capturedStart(), match.capturedLength()};

        double score = 0.0;
        QVector<QString> sigs;

        for(const auto& vald : validators_) {
            if(vald->eval(match.capturedView().toString(), ctx)) {
                score += vald->getScore();
                sigs.push_back(vald->wrapMatch(match.capturedView().toString()));
            }
        }

        if(score <= 0.0)
            continue;

        results.push_back({match.capturedView().toString(), ctx.position, type_, std::min(score, 1.0), sigs});
    }

    return results;
}
