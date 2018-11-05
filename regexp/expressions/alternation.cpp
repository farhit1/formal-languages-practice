#include "alternation.h"


namespace regexp {
namespace expressions {

Positions Alternation::match(const std::string &s, size_t start) const {
    auto lMatches = l_->match(s, start);
    auto rMatches = r_->match(s, start);

    Positions result;
    std::set_union(lMatches.begin(), lMatches.end(),
                   rMatches.begin(), rMatches.end(),
                   std::back_inserter(result));
    return result;
}

} // namespace expressions
} // namespace regexp
