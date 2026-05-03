#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "scan_result.hpp"
#include <QString>
#include <algorithm>

class Validator {
    QString name_;

    double score_;

    QString description_;

    QString getWindow(const Context &ctx, qsizetype radius = 50) {
        const size_t start = (ctx.position > radius) ? ctx.position - radius : 0;
        const size_t end = std::min(ctx.fullData.size(), ctx.position + ctx.length + radius);
        return QString(ctx.fullData.mid(start, end - start));
    }

public:
    Validator(QString name, double score, QString description) : name_(std::move(name)), score_(score),
                                                                 description_(std::move(description)) {
    }

    QString getName() const { return name_; }

    QString getDescription() const { return description_; };

    double getScore() const { return score_; };

    QString wrapMatch(QString s) const { return name_ + ":" + QString::number(score_); };

    virtual bool eval(QString s, Context ctx) = 0;

    virtual ~Validator() = default;
};

#endif // VALIDATOR_HPP
