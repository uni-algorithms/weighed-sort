#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "weighed-sort.hpp"

TEST_CASE("test provided : 3 2 4 1") {
    std::stringstream s("4\n"
                        "3 2 4 1");
    REQUIRE(swaps_weight(2, 9) == uncovered(s));
}


TEST_CASE("4 3 2 1") {
    std::stringstream s("4\n"
                        "4 3 2 1");
    REQUIRE(swaps_weight(2, 10) == uncovered(s));
}


TEST_CASE("12 3 2 4 13 1 5 8 14 7 9 6 10 15 17 16 11") {
    std::stringstream s("17\n"
                        "12 3 2 4 13 1 5 8 14 7 9 6 10 15 17 16 11");
    REQUIRE(swaps_weight(10, 151) == uncovered(s));
}

TEST_CASE("2 5 6 1 8 4 3 7") {
    std::stringstream s("8\n"
                        "2 5 6 1 8 4 3 7");
    REQUIRE(swaps_weight(7, 42) == uncovered(s));
}

TEST_CASE("4 5 2 3 1") {
    std::stringstream s("5\n"
                        "4 5 2 3 1");
    REQUIRE(swaps_weight(4, 18) == uncovered(s));
}