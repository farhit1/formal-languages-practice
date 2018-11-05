#include "regexp_impl.h"

#include "expression/alternation.h"
#include "expression/concatenation.h"
#include "expression/empty.h"
#include "expression/kleeneStar.h"
#include "expression/letter.h"

#include <stack>


namespace regexp {

namespace {

using StackType = std::stack<std::unique_ptr<expressions::Expression>>;

template<size_t ArgsN, typename Operation>
struct Join {
    template<typename... Operations>
    static void impl(StackType &stack, Operations... operations) {
        if (stack.empty())
            throw ParseError();
        auto operation = std::move(stack.top());
        stack.pop();
        Join<ArgsN - 1, Operation>::impl(stack, std::move(operation), std::move(operations)...);
    }
};

template<typename Operation>
struct Join<0, Operation> {
    template<typename... Operations>
    static void impl(StackType &stack, Operations... operations) {
        stack.push(std::make_unique<Operation>(std::move(operations)...));
    }
};

template<typename Operation, size_t ArgsN>
void join(StackType &stack) {
    Join<ArgsN, Operation>::impl(stack);
}

} // anonymous namespace

const std::string RegexpImpl::ALPHABET_ = "abc";

RegexpImpl::RegexpImpl(const std::string& s) {
    StackType expressionsStack;

    for (char c : s) {
        if (ALPHABET_.find(c) != std::string::npos)
            expressionsStack.push(std::make_unique<expressions::Letter>(c));
        else if (c == '.')
            join<expressions::Concatenation, 2>(expressionsStack);
        else if (c == '1')
            expressionsStack.push(std::make_unique<expressions::Empty>());
        else if (c == '+')
            join<expressions::Alternation, 2>(expressionsStack);
        else if (c == '*')
            join<expressions::KleeneStar, 1>(expressionsStack);
        else
            throw ParseError();
    }

    if (expressionsStack.size() != 1)
        throw ParseError();
    expression_ = std::move(expressionsStack.top());
}

bool RegexpImpl::has(const std::string& s) const {
    auto result = expression_->match(s, 0);
    return !result.empty() && result.back() == s.length();
}

std::unique_ptr<Regexp> createRegexp(const std::string &s) {
    return std::make_unique<RegexpImpl>(s);
}

} // namespace regexp
