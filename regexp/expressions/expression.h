#pragma once

#include <regexp/regexp.h>

#include <string>
#include <vector>


namespace regexp {
namespace expressions {

using Positions = std::vector<size_t>;

class Expression {
public:
    virtual ~Expression() = default;

    explicit Expression(int id);

    Positions match(const std::string &s, size_t start, Cache& cache) const;

private:
    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const = 0;

    int id_;
};

class UnaryExpression : public Expression {
public:
    UnaryExpression(std::unique_ptr<Expression> enclosed, int id);

protected:
    std::unique_ptr<Expression> enclosed_;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r, int id);

protected:
    std::unique_ptr<Expression> l_;
    std::unique_ptr<Expression> r_;
};

} // namespace expressions
} // namespace regexp
