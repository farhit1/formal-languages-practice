cmake_minimum_required(VERSION 3.8)
project(formalprac)

set(CMAKE_CXX_STANDARD 17)
include_directories(regexp/include)

include_directories(/usr/local/include)

set(SOURCE_FILES
        regexp/regexp_impl.cpp
        regexp/expressions/expression.cpp
        regexp/expressions/alternation.cpp
        regexp/expressions/kleene_star.cpp
        regexp/expressions/empty.cpp
        regexp/expressions/letter.cpp
        regexp/expressions/concatenation.cpp)

add_executable(formalprac main.cpp ${SOURCE_FILES})
add_executable(test_formalprac test.cpp ${SOURCE_FILES})

target_link_libraries(test_formalprac /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
