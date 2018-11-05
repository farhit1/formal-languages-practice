#pragma once

#include "expression.h"


namespace regexp {
namespace expressions {

class Concatenation : public Expression, public Binary {
public:
    using Binary::Binary;

    virtual Positions match(const std::string& s, size_t start) const override;
};

} // namespace expressions
} // namespace regexp
