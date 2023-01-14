#include "stripGenerator.h"
#include "assert.h"

void testCompatability(const std::vector<int>& stripA, const std::vector<int>& stripB, bool expectedResult) {
    bool result = isCompatible(stripToInt(stripA), stripToInt(stripB));
    assert(result == expectedResult);
}

void testCompatable_01() {
    std::vector<int> stripA { 3, 2, 2, 3 };
    std::vector<int> stripB { 2, 2, 2, 2, 2};
    testCompatability(stripA, stripB, true);
}

void testInCompatable_01() {
    std::vector<int> stripA { 3, 2, 2, 3 };
    std::vector<int> stripB { 3, 3, 2, 2 };
    testCompatability(stripA, stripB, false);
}

void testStripGeneration_01() {
    stripGenerator generator(12, 3);
    generator.generateValidStrips();
    size_t numStrips = 1; // 3, 3, 3, 3 - cannot permute
    ++numStrips; // 2, 2, 2, 2, 2, 2 - cannot permute
    numStrips += (5 * 4 *  3 * 2) / (2 * 3 * 2); // formula for number of permutations of { 2, 2, 2, 3, 3 }
    assert(generator.allStrips_.size() == numStrips);
}

void testStripGeneration_02() {
    stripGenerator generator(9, 3);
    generator.generateValidStrips();
    assert(generator.allStrips_.size() == 5);
    generator.generateCompatibleStrips();
    size_t compatabilityCount = 0;
    for (const auto& c : generator.allCompatibleStrips_) {
        compatabilityCount += c.size();
    }
    assert(compatabilityCount == 6);
    auto combinations = generator.calculateOptions();
    assert(combinations == 8);
}

int main() {
    testCompatable_01();
    testInCompatable_01();
    testStripGeneration_02();
    testStripGeneration_01();

    std::cout << "Tests Pass\n";
}