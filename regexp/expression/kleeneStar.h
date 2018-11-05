#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class KleeneStar : public Expression, public Unary {
    using Unary::Unary;

    virtual Positions match(const std::string &s, size_t start) const override;
};

} // namespace expression
} // namespace regexp
