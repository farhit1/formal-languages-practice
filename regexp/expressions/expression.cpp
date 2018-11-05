#include "expression.h"


namespace regexp {
namespace expressions {

Unary::Unary(std::unique_ptr<Expression> enclosed)
        : enclosed_ (std::move(enclosed))
{}

Binary::Binary(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : l_(std::move(l))
        , r_(std::move(r))
{}

} // namespace expressions
} // namespace regexp
