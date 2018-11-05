#include <regexp/regexp.h>

#include <gtest/gtest.h>


namespace {

using namespace testing;
using namespace regexp;

TEST(RegexpTest, CheckParseError) {
    struct {
        std::string alpha;
        bool parsable;
    } tests[] = {
        { "a", true },
        { "ab", false },
        { "ab.", true },
        { "a*", true },
        { ".", false },
        { "1", true },
        { "+a", false }
    };

    for (const auto& test : tests) {
        try {
            auto language = createRegexp(test.alpha);
            ASSERT_TRUE(test.parsable);
        }
        catch (ParseError&) {
            ASSERT_FALSE(test.parsable);
        }
    }
}

TEST(RegexpTest, CheckIfLanguageHasWord) {
    struct {
        std::string alpha;
        std::vector<std::pair<std::string, bool>> words;
    } tests[] = {
        {
            "ab+",
            {
                { "", false },
                { "a", true },
                { "b", true },
                { "c", false },
                { "ab", false }
            }
        },
        {
            "ab.a*+",
            {
                { "", true },
                { "a", true },
                { "b", false },
                { "ab", true },
                { "aa", true },
                { "aaa", true },
                { "abaa", false }
            }
        },
        {
            "ab+c.aba.*.bac.+.+*",
            {
                { "abacb", false },
                { "abac", true }
            }
        },
        {
            "acb..bab.c.*.ab.ba.+.+*a.",
            {
                { "cb", false },
                { "c", false },
                { "", false }
            }
        },
        {
            "1a+",
            {
                { "", true },
                { "a", true },
                { "b", false },
                { "aa", false }
            }
        }
    };

    for (const auto& test : tests) {
        auto language = createRegexp(test.alpha);
        for (const auto &[word, has] : test.words) {
            ASSERT_EQ(has, language->has(word));
        }
    }
}

} // anonymous namespace


int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
