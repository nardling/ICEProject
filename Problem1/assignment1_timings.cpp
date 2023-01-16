#include "dumb_container.h"
#include <chrono>
#include <iostream>
#include <cstdint>

#define ARRAY_SIZE 128000000

int main() {    
    dumbContainer container(ARRAY_SIZE);
    srand((unsigned)time(0));

    container.insertFirst((double)(rand() % 100000));

    for (int i = 1; i < ARRAY_SIZE; ++ i){

        // container.insertAtTail((double)(rand() % 100000));
        container.insertNumberIterating((double)(rand() % 100000));
        if (0 == (i % 10000)) {
            auto now = std::chrono::system_clock::now();
        
            auto nowTime = std::chrono::system_clock::to_time_t(now);
        
            std::cout << i << ":" << std::ctime(&nowTime);
        }
    }

    return 0;
}