#include "topFivePctContainer.h"
#include <chrono>
#include <iostream>

#define ARRAY_SIZE 128000000

int main() {
    splitList splits(4, 10);
    topFivePctContainer container(splits, ARRAY_SIZE);
    srand((unsigned)time(0));

    container.insertFirst((double)(rand() % 100000));
    container.insertSecond((double)(rand() % 100000));

    for (int i = 2; i < ARRAY_SIZE; ++ i){
        container.insertNumber((double)(rand() % 100000));
        std::cout << container.counter_ << ": ";
        std::cout << container.getMarker() << '\n';
    }

    return 0;
}