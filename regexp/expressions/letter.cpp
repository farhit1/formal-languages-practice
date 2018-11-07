#include "letter.h"


namespace regexp {
namespace expressions {

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
} // namespace regexp
