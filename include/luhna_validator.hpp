#ifndef LUHNAVALIDATOR_HPP
#define LUHNAVALIDATOR_HPP

#include "validator.hpp"

class LuhnaValidator : public Validator
{
public:
    LuhnaValidator();

    bool eval(QString s, Context ctx) override;
};

#endif // LUHNAVALIDATOR_HPP
