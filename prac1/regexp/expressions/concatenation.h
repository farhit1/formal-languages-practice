#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class Concatenation : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual Positions match_(const std::string& s, size_t start, Cache& cache) const override;
};

} // namespace expressions
} // namespace regexp
