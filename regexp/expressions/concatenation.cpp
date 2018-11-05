#include "concatenation.h"

#include <set>


namespace regexp {
namespace expressions {

Positions Concatenation::match(const std::string& s, size_t start) const {
    std::set<size_t> positions;
    for (size_t position : l_->match(s, start)) {
        auto match = r_->match(s, position);
        positions.insert(match.begin(), match.end());
    }

    return Positions(positions.begin(), positions.end());
}

} // namespace expressions
} // namespace regexp

