#include "regexp_impl.h"

#include "expressions/alternation.h"
#include "expressions/concatenation.h"
#include "expressions/empty.h"
#include "expressions/kleene_star.h"
#include "expressions/letter.h"

#include <stack>


namespace regexp {

namespace {

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

} // anonymous namespace

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

bool RegexpImpl::has(const std::string& s, Cache* cache) const {
    std::unique_ptr<Cache> ownCache;
    if (!cache)
        ownCache = std::make_unique<Cache>(expressions_);
    else if (cache->empty())
        *cache = Cache(expressions_);
    Cache& appliedCache = (cache ? *cache : *ownCache);

    auto result = expression_->match(s, 0, appliedCache);
    return std::find(result.begin(), result.end(), s.length()) != result.end();
}

std::unique_ptr<Regexp> createRegexp(const std::string &s) {
    return std::make_unique<RegexpImpl>(s);
}

} // namespace regexp
