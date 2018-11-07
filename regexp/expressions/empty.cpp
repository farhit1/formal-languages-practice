#include "empty.h"


namespace regexp {
namespace expressions {

Positions Empty::match_(const std::string &s, size_t start, Cache& /* cache */) const {
    return {start};
}

} // namespace expressions
} // namespace regexp
