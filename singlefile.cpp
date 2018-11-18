#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

////////////////////
/// Declarations ///
////////////////////

namespace regexp {

using Cache = std::vector<std::unordered_map<int, std::vector<size_t>>>;

class Regexp {
public:
    virtual ~Regexp() = default;

    virtual bool has(const std::string &s) const = 0;
    virtual bool has(const std::string &s, Cache* cache) const = 0;
};

struct ParseError : public std::exception {};

std::unique_ptr<Regexp> createRegexp(const std::string &s);


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


class Alternation : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;
};

class Concatenation : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual Positions match_(const std::string& s, size_t start, Cache& cache) const override;
};

class Empty : public Expression {
public:
    using Expression::Expression;

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;
};

class KleeneStar : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;
};

class Letter : public Expression {
public:
    Letter(char letter, int id);

    virtual Positions match_(const std::string &s, size_t start, Cache& cache) const override;

private:
    char letter_;
};

} // namespace expressions


class RegexpImpl : public Regexp {
public:
    explicit RegexpImpl(const std::string& s);

    virtual bool has(const std::string& s) const override;
    virtual bool has(const std::string& s, Cache* cache) const override;

private:
    std::unique_ptr<expressions::Expression> expression_;

    size_t expressions_ = 0;
};

} // namespace regexp


///////////////////
/// Definitions ///
///////////////////

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

Positions Alternation::match_(const std::string &s, size_t start, Cache& cache) const {
    auto lMatches = l_->match(s, start, cache);
    auto rMatches = r_->match(s, start, cache);

    Positions result;
    std::set_union(lMatches.begin(), lMatches.end(),
                   rMatches.begin(), rMatches.end(),
                   std::back_inserter(result));
    return result;
}

Positions Concatenation::match_(const std::string& s, size_t start, Cache& cache) const {
    std::set<size_t> positions;
    for (size_t position : l_->match(s, start, cache)) {
        auto match = r_->match(s, position, cache);
        positions.insert(match.begin(), match.end());
    }

    return Positions(positions.begin(), positions.end());
}

Positions Empty::match_(const std::string &s, size_t start, Cache& /* cache */) const {
    return {start};
}

Positions KleeneStar::match_(const std::string& s, size_t start, Cache& cache) const {
    std::set<size_t> toBeMatched = {start};
    Positions result;

    while (!toBeMatched.empty()) {
        size_t position = *toBeMatched.begin();
        toBeMatched.erase(toBeMatched.begin());
        for (auto newPosition : enclosed_->match(s, position, cache)) {
            if (newPosition != position)
                toBeMatched.insert(newPosition);
        }

        result.push_back(position);
    }

    return result;
}

Letter::Letter(char letter, int id)
        : letter_(letter)
        , Expression(id)
{}

Positions Letter::match_(const std::string &s, size_t start, Cache& /* cache */) const {
    if (start == s.size())
        return {};
    if (s[start] != letter_)
        return {};
    return {start + 1};
}

} // namespace expressions


using namespace expressions;
using StackType = std::stack<std::unique_ptr<Expression>>;

const std::string ALPHABET = "abc";

template<size_t ArgsN, typename Operation>
struct Join {
    template<typename... Args>
    static void impl(StackType &stack, Args... operations) {
        if (stack.empty())
            throw ParseError();
        auto operation = std::move(stack.top());
        stack.pop();
        Join<ArgsN - 1, Operation>::impl(stack, std::move(operation), std::move(operations)...);
    }
};

template<typename Operation>
struct Join<0, Operation> {
    template<typename... Args>
    static void impl(StackType &stack, Args... operations) {
        stack.push(std::make_unique<Operation>(std::move(operations)...));
    }
};

RegexpImpl::RegexpImpl(const std::string& s) {
    StackType expressionsStack;

    for (char c : s) {
        switch (c) {
            case '.':
                Join<2, Concatenation>::impl(expressionsStack, expressions_++);
                break;
            case '1':
                expressionsStack.push(std::make_unique<Empty>(expressions_++));
                break;
            case '+':
                Join<2, Alternation>::impl(expressionsStack, expressions_++);
                break;
            case '*':
                Join<1, KleeneStar>::impl(expressionsStack, expressions_++);
                break;
            default:
                if (ALPHABET.find(c) == std::string::npos)
                    throw ParseError();
                expressionsStack.push(std::make_unique<Letter>(c, expressions_++));
        }
    }

    if (expressionsStack.size() != 1)
        throw ParseError();
    expression_ = std::move(expressionsStack.top());
}

bool RegexpImpl::has(const std::string& s) const {
    Cache ownCache;
    return has(s, &ownCache);
}

bool RegexpImpl::has(const std::string& s, Cache* cache) const {
    if (cache->empty())
        *cache = Cache(expressions_);

    auto result = expression_->match(s, 0, *cache);
    return std::find(result.begin(), result.end(), s.length()) != result.end();
}

std::unique_ptr<Regexp> createRegexp(const std::string &s) {
    return std::make_unique<RegexpImpl>(s);
}

} // namespace regexp


int main() {
    std::string alpha;
    std::cin >> alpha;

    try {
        auto language = regexp::createRegexp(alpha);
        std::string u;
        std::cin >> u;

        regexp::Cache cache;
        while (true) {
            if (language->has(u, &cache)) {
                std::cout << u.length() << std::endl;
                break;
            }
            if (u.empty()) {
                std::cout << "INF" << std::endl;
                break;
            }
            u.pop_back();
        }
    }
    catch (regexp::ParseError&) {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}
