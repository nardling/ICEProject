#include "topFivePctContainer.h"
#include <chrono>
#include <iostream>
#include "assert.h"

#define ARRAY_SIZE 1000000

bool checkVectorOrder(node* head) {
    node* lclHead = head;
    while (lclHead->next && lclHead->value <= lclHead->next->value) {
        lclHead = lclHead->next;
    }
    return lclHead->next == nullptr;
}

void printList(node* head) {
    node* lclHead = head;
    while (lclHead) {
        std::cout << lclHead->value << '\n';
        lclHead = lclHead->next;
    }
}

void testPctile_01() {
    splitList splits(4, 8, ARRAY_SIZE);
    topFivePctContainer container(splits, ARRAY_SIZE);
    container.insertFirst(0);
    container.insertSecond(1);

    for (int i = 2; i < 45; ++i) {
        container.insertNumber(i);

        switch(container.counter_) {
            case 18:
                assert(container.getMarker() == 17);
                break;
            case 19:
                assert(container.getMarker() == 18);
                break;
            case 20:
                // .95 of 20 is 19. The number should be bigger than 19 others
                assert(container.getMarker() == 19);
                break;
            case 21:
                // .95 of 21 is 19.95. The number should be bigger than 19 others
                assert(container.getMarker() == 19);
                break;
            case 22:
                // .95 of 22 is 20.9. The number should be bigger than 20 others
                assert(container.getMarker() == 20);
                break;
            case 40:
                // .95 of 40 is 38. The number should be bigger than 38 others
                assert(container.getMarker() == 38);
                break;
            case 41:
                // .95 of 41 is 38.95. The number should be bigger than 38 others
                assert(container.getMarker() == 38);
                break;
            case 42:
                // .95 of 42 is 39.9. The number should be bigger than 39 others
                assert(container.getMarker() == 39);
                break;
            case 43:
                // .95 of 43 is 40.85. The number should be bigger than 40 others
                assert(container.getMarker() == 40);
                break;
            case 44:
                // .95 of 43 is 41.8. The number should be bigger than 41 others
                assert(container.getMarker() == 41);
                break;
            default:
                break;
        }
    }
    std::cout << "testPctile_01 Passes\n";
}

void testRandomInsert_01() {
    splitList splits(4, 2, ARRAY_SIZE);
    topFivePctContainer container(splits, ARRAY_SIZE);
    container.insertFirst(0);
    container.insertSecond(1);

    container.insertNumber(5);    
    container.insertNumber(7);
    container.insertNumber(3);
    container.insertNumber(6);
    container.insertNumber(9);
    container.insertNumber(2);
    container.insertNumber(4);

    assert(checkVectorOrder(container.numbers_));
    std::cout << "testRandomInsert_01 Passes\n";
}

void testSplitOrder_01() {
    splitList splits(4, 2, ARRAY_SIZE);
    topFivePctContainer container(splits, ARRAY_SIZE);
    container.insertFirst(0);
    container.insertSecond(1);
    for (int i = 2; i < 100000; ++ i){
        container.insertNumber((double)(rand() % 100000));
    }
    assert(checkVectorOrder(container.numbers_));
    assert(checkVectorOrder(splits.splits_[0]));
    assert(checkVectorOrder(splits.splits_[1]));
    assert(checkVectorOrder(splits.splits_[2]));
    assert(checkVectorOrder(splits.splits_[3]));
    std::cout << "testSplitOrder_01 Passes\n";
}

void testSplitSize_01() {
    splitList splits(4, 2, 1024);
    topFivePctContainer container(splits, 1024);
    container.insertFirst(0);
    container.insertSecond(1);
    for (int i = 2; i < 1024; ++ i){
        container.insertNumber((double)(rand() % 100000));
    }
    assert(checkVectorOrder(container.numbers_));
    // std::cout << "Test 1: " << splits.counter_ << '\n';
    assert(splits.counter_ < 965 && splits.counter_ > 960);
    std::cout << "testSplitSize_01 Passes\n";
}

void testSplitSize_02() {
    splitList splits(4, 4, 1024);
    topFivePctContainer container(splits, 1024);
    container.insertFirst(0);
    container.insertSecond(1);
    for (int i = 2; i < 1024; ++ i){
        container.insertNumber((double)(rand() % 100000));
    }
    assert(checkVectorOrder(container.numbers_));
    // std::cout << "Test 2: " << splits.counter_ << '\n';
    assert(splits.counter_ < 348 && splits.counter_ > 340);
    std::cout << "testSplitSize_02 Passes\n";
}

int main() {
    testPctile_01();
    testRandomInsert_01();
    testSplitOrder_01();
    testSplitSize_01();
    testSplitSize_02();
    std::cout << "All Tests Pass\n";
}