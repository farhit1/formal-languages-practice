#include "kleeneStar.h"

#include <set>


namespace regexp {
namespace expressions {

Positions KleeneStar::match(const std::string& s, size_t start) const {
    std::set<size_t> toBeMatched = {start};
    Positions result;

    while (!toBeMatched.empty()) {
        size_t position = *toBeMatched.begin();
        toBeMatched.erase(toBeMatched.begin());
        for (auto newPosition : enclosed_->match(s, position)) {
            if (newPosition != position)
                toBeMatched.insert(newPosition);
        }

        result.push_back(position);
    }

    return result;
}

} // namespace expression
} // namespace regexp
