#include "stripGenerator.h"

/* Solution Summary:

    1. Generate all combinations of 2's and 3's that sum to 30
    2. Generate all unique permutations of those numbers
    3. Create a graph structure pointing from a strip to it's compatible neighbors
    4. Use the graph structure to iterate through the steps
        a. We have 4 strips, and 1 is compatible with 2 and 4, 2 is compatible with 1, 3 is compatible with 4 and 4 is compatible with 3 and 1:
            1: 2, 4
            2: 1
            3: 4
            4: 3, 1
        b. First strip can be any of the 4:
            1: 1
            2: 1
            3: 1
            4: 1
        c. Second strip possibilities are measured by previous step
            1: 2 (2, 4)
            2: 1 (1)
            3: 1 (4)
            4: 2 (1, 3)
        d. Again
            1: 3 (1 way from 2, 2 ways from 4)
            2: 2 (2 ways from 1)
            3: 2 (2 ways from 4)
            4: 3 (2 ways from 1, 1 way from 3)
        
        and so on.  After 11 steps, sum up the values.

    The answer to the question is 1007720438618812
*/

int main() {
    stripGenerator generator(30, 11);

    generator.generateValidStrips();
    generator.generateCompatibleStrips();

    auto totalOptions = generator.calculateOptions();

    std::cout << "Total Possible Combinations: " << totalOptions << '\n';
    return 0;
}