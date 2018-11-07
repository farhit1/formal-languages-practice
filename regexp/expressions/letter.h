#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class Letter : public Expression {
public:
    explicit Letter(char letter, int id);

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;

private:
    char letter_;
};

} // namespace expressions
} // namespace regexp
