#include "node.h"
#include "stdlib.h"
#include <vector>
#include <cstddef>
#include <math.h>
#include <stdexcept>
#include <iostream>

class splitList {
    public:
        splitList(int splitCount, int splitPct, size_t numberCount = 128000000) : splitCount_(splitCount), splitPct_(splitPct) {
            if (pow(2, floor(log2(splitPct))) != splitPct || splitPct < 2) {
                throw new std::runtime_error("Split Pct Must Be a Power of 2 greater than 1");
            }
            splits_.reserve(splitCount);
            lastSeenSplits_.reserve(splitCount);
            for (int i = 0; i < splitCount; ++i) {
                splits_[i] = nullptr;
                lastSeenSplits_[i] = nullptr;
            }

            splitFilters_.reserve(splitCount);
            int lclSplitPct = splitPct;
            for (int i = (splitCount - 1); i >= 0; --i) {
                splitFilters_[i] = lclSplitPct - 1;
                lclSplitPct *= splitPct;
            }
            numbers_ = (node*)malloc(sizeof(node) * numberCount);
        }

        ~splitList() {
            free((void*)numbers_);
            for (auto p : splits_) {
                delete(p);
            }
            for (auto p : lastSeenSplits_) {
                delete(p);
            }
        }

    void updateNewHeadForSplits(node* newHead) {
        node* child = newHead;
        for (int i = (splitCount_ - 1); i >= 0; --i) {
            node* splitStart = splits_[i];
            node* newNode = &numbers_[counter_++]; //new node();
            newNode->value = newHead->value;
            newNode->prev = child;
            newNode->next = splitStart;
            splits_[i] = newNode;
            child = newNode;
        }
    }

    void insertSplit(node* newNode, size_t level, size_t counter) {
        // if ((rand() % 100) < splitPct_) {
            // std::cout << "Counter: " << counter << " Level " << level << " filter " << splitFilters_[level];
        if ((counter & splitFilters_[level]) == 0) {
            // std::cout << " Passes\n";
            node* lastSeen = lastSeenSplits_[level];
            node* newSplit = &numbers_[counter_++]; //new node();
            newSplit->value = newNode->value;
            newSplit->next = lastSeen->next;
            lastSeen->next = newSplit;
            newSplit->prev = newNode;
            if (level > 0)
                insertSplit(newSplit, level - 1, counter);
        } else {
            // std::cout << " Does Not Pass\n";
        }
    }

    void insertSplit(node* newNode, size_t counter) {
        insertSplit(newNode, splitCount_ - 1, counter);
    }

    node* findInsertPointInSplits(const double& newNumber, node* prevStart, int splitIndex) {
        node* start = prevStart ? prevStart : splits_[splitIndex];

        if (start == nullptr) {
            throw new std::runtime_error("Start is nullptr");
        }

        while (start->next && start->next->value < newNumber) {
            start = start->next;
        }
        // repurposing here for pointer to next level down
        lastSeenSplits_[splitIndex] = start;
        return start->prev;
    }

    node* findInsertPointInSplits(const double& newNumber) {
        int splitIndex = 0;
        node* returnValue = nullptr;
        while (splitIndex < splitCount_) {
            returnValue = findInsertPointInSplits(newNumber, returnValue, splitIndex);
            ++splitIndex;
        }
        return returnValue;
    }

    public:
        std::vector<node*> splits_;
        std::vector<node*> lastSeenSplits_;
        std::vector<int> splitFilters_;
        node* numbers_ = nullptr;
        size_t counter_ = 0;
        const int splitCount_;
        const int splitPct_;
};