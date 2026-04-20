#include "../include/luhna_validator.hpp"

LuhnaValidator::LuhnaValidator() : Validator("luhna", 0.5, "Поиск номера по алгоритму Луна") {}

bool LuhnaValidator::eval(QString s, Context)
{
    int sum = 0;
    bool alternate = false;

    for(int i = s.size() - 1; i >= 0; --i) {
        if(!s[i].isDigit())
            continue;

        int n = s[i].toLatin1() - '0';

        if(alternate) {
            n *= 2;
            if(n > 9)
                n -= 9;
        }

        sum += n;
        alternate = !alternate;
    }

    return sum % 10 == 0;
}
