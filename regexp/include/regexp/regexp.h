#pragma once

#include <string>


namespace regexp {

class Regexp {
public:
    virtual ~Regexp() = default;

    virtual bool has(const std::string &s) const = 0;
};

struct ParseError : public std::exception {};

std::unique_ptr<Regexp> createRegexp(const std::string &s);

} // namespace regexp
