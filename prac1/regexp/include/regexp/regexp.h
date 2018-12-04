#pragma once

#include <string>
#include <unordered_map>
#include <vector>


namespace regexp {

using Cache = std::vector<std::unordered_map<int, std::vector<size_t>>>;

class Regexp {
public:
    virtual ~Regexp() = default;

    virtual bool has(const std::string &s) const = 0;
    virtual bool has(const std::string &s, Cache* cache) const = 0;
};

struct ParseError : public std::exception {};

std::unique_ptr<Regexp> createRegexp(const std::string &s);

} // namespace regexp
