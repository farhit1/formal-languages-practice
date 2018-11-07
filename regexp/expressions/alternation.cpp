#include "alternation.h"


namespace regexp {
namespace expressions {

Positions Alternation::match_(const std::string &s, size_t start, Cache& cache) const {
    auto lMatches = l_->match(s, start, cache);
    auto rMatches = r_->match(s, start, cache);

    Positions result;
    std::set_union(lMatches.begin(), lMatches.end(),
                   rMatches.begin(), rMatches.end(),
                   std::back_inserter(result));
    return result;
}

} // namespace expressions
} // namespace regexp
