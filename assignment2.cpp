#include "stripGenerator.h"

int main() {
    stripGenerator generator(30, 11);

    generator.generateValidStrips();
    generator.generateCompatibleStrips();
    
    // printCompatibleStrips(allCompatibleStrips);

    auto totalOptions = generator.calculateOptions();

    std::cout << "Total Possible Combinations: " << totalOptions << '\n';
    return 0;
}