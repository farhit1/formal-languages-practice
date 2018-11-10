#include "expression.h"


namespace regexp {
namespace expressions {

Expression::Expression(int id)
        : id_(id)
{}

Positions Expression::match(const std::string &s, size_t start, Cache& cache) const {
    auto& expressionCache = cache[id_];
    if (expressionCache.find(start) == expressionCache.end())
        expressionCache[start] = match_(s, start, cache);
    return expressionCache[start];
}

UnaryExpression::UnaryExpression(std::unique_ptr<Expression> enclosed, int id)
        : enclosed_(std::move(enclosed))
        , Expression(id)
{}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r, int id)
        : l_(std::move(l))
        , r_(std::move(r))
        , Expression(id)
{}

} // namespace expressions
} // namespace regexp
