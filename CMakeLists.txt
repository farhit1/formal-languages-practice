cmake_minimum_required(VERSION 3.8)
project(formalprac)

set(CMAKE_CXX_STANDARD 17)
include_directories(regexp/include)

include_directories(/usr/local/include)

set(SOURCE_FILES
        regexp/regexp_impl.cpp
        regexp/expression/expression.cpp
        regexp/expression/alternation.cpp
        regexp/expression/kleeneStar.cpp
        regexp/expression/empty.cpp
        regexp/expression/letter.cpp
        regexp/expression/concatenation.cpp)

add_executable(formalprac main.cpp ${SOURCE_FILES})
add_executable(test_formalprac test.cpp ${SOURCE_FILES})

target_link_libraries(test_formalprac /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)
