#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class KleeneStar : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;
};

} // namespace expressions
} // namespace regexp
