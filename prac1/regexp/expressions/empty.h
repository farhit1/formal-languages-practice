#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class Empty : public Expression {
public:
    using Expression::Expression;

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;
};

} // namespace expressions
} // namespace regexp
