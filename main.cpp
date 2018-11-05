#include <iostream>

#include <regexp/regexp.h>


int main() {
    std::string alpha;
    std::cin >> alpha;

    try {
        auto language = regexp::createRegexp(alpha);
        std::string u;
        std::cin >> u;
        while (true) {
            if (language->has(u)) {
                std::cout << u.length() << std::endl;
                break;
            }
            if (u.empty()) {
                std::cout << "INF" << std::endl;
                break;
            }
            u.pop_back();
        }
    }
    catch (regexp::ParseError&) {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}
