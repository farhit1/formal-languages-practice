#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class Empty : public Expression {
public:
    Empty() = default;

    virtual Positions match(const std::string &s, size_t start) const override;
};

} // namespace expressions
} // namespace regexp
