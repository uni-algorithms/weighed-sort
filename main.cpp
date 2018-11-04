#include <cassert>
#include "weighed-sort.hpp"

auto main() -> int {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    assert(input);
    assert(output);

    output << uncovered(input);

    input.close();
    output.close();
    return 0;
}