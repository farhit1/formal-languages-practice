#include "empty.h"


namespace regexp {
namespace expressions {

Positions Empty::match(const std::string &s, size_t start) const {
    return {start};
}

} // namespace expression
} // namespace regexp
