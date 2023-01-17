#include "topFivePctContainer.h"
#include <chrono>
#include <iostream>
#include <iomanip>

#define ARRAY_SIZE 128000000
#define CARDINALITY 128000000
#define PRINT_INTERVAL 524287

/* Solution Summary:

    The solution is implemented with an ordered doubly-linked list, indexed by a binary search (the splitList)
    All memory is pre-allocated
    The list maintains a pointer to the first element that's greater than 95% of the rest of the list.
        Each 20 items causes the pointer to move backwards one element, and each item that's greater than the current
        95th% value causes the pointer to move forward one element.
    The value at that pointer is available via container.getMarker().  Currently it only displays that at intervals.
    Once the count of the list reaches 5% of the max, the list starts to reject any numbers lower than the 
        lowest number that could be the solution.  So if there are 1000 numbers, and the list has 50 numbers
        and the lowest number is 55, and the next lowest is 99, all numbers lower than 55 are rejected, and as soon
        as a number higher than 55 is accepted, the lowLimit pointer moves to 99
    

    This takes about 4 minutes 45 seconds on my computer, which is an old laptop.
    It's infinitely better than the naive approach of maintaining an ordered list without indexing, which didn't finish at all.
 */


double getRand() {
    return (double)(rand() % CARDINALITY);
}

int main() {
    splitList splits(14, 2, ARRAY_SIZE);
   
    topFivePctContainer container(splits, ARRAY_SIZE);
    srand((unsigned)time(0));

    container.insertFirst(getRand());
    container.insertSecond(getRand());

    for (int i = 2; i < ARRAY_SIZE; ++ i){
        container.insertNumber(getRand());
        // std::cout << container.getMarker() << '\n';
        if ((container.counter_ & PRINT_INTERVAL) == 0) {
            auto now = std::chrono::system_clock::now();
        
            auto nowTime = std::chrono::system_clock::to_time_t(now);
        
            std::cout << "At " << container.counter_ << ": 95th percentile: " << std::setprecision(9) << container.getMarker() << " Time: " << std::ctime(&nowTime);
        }
    }

    std::cout << "Final 95th percentile: " << std::setprecision(9) << container.getMarker() << '\n';

    return 0;
}
