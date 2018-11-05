#pragma once

#include <string>
#include <vector>


namespace regexp {
namespace expressions {

using Positions = std::vector<size_t>;

class Expression {
public:
    virtual ~Expression() = default;

    virtual Positions match(const std::string &s, size_t start) const = 0;
};

class Unary {
public:
    explicit Unary(std::unique_ptr<Expression> enclosed);

protected:
    std::unique_ptr<Expression> enclosed_;
};

class Binary {
public:
    Binary(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r);

protected:
    std::unique_ptr<Expression> l_;
    std::unique_ptr<Expression> r_;
};

} // namespace expression
} // namespace regexp
