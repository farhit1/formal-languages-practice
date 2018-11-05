#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class Letter : public Expression {
public:
    explicit Letter(char letter);

    virtual Positions match(const std::string &s, size_t start) const override;

private:
    char letter_;
};

} // namespace expression
} // namespace regexp
