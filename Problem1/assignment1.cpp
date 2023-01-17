#include "topFivePctContainer.h"
#include <chrono>
#include <iostream>

// On my laptop, RAND MAX is 2147483647

#define ARRAY_SIZE 128000000
#define CARDINALITY 128000000
#define PRINT_INTERVAL 524287

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
        // std::cout << container.counter_ << ": ";
        // std::cout << container.getMarker() << '\n';
        if ((container.counter_ & PRINT_INTERVAL) == 0) {
            auto now = std::chrono::system_clock::now();
        
            auto nowTime = std::chrono::system_clock::to_time_t(now);
        
            std::cout << "Time At " << container.counter_ << ":" << std::ctime(&nowTime);
        }
    }

    return 0;
}
