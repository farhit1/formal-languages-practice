#include "letter.h"


namespace regexp {
namespace expressions {

Letter::Letter(char letter)
        : letter_(letter)
{}

Positions Letter::match(const std::string &s, size_t start) const {
    if (start == s.size())
        return {};
    if (s[start] != letter_)
        return {};
    return {start + 1};
}

} // namespace expressions
} // namespace regexp
