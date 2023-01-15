#include "node.h"
#include "stdlib.h"
#include <vector>
#include <cstddef>

class splitList {
    public:
        splitList(int splitCount, int splitPct) : splitCount_(splitCount), splitPct_(splitPct) {
            splits_.reserve(splitCount_);
            lastSeenSplits_.reserve(splitCount_);
        }

    void updateNewHeadForSplits(node* newHead) {
        node* child = newHead;
        for (int i = (splitCount_ - 1); i >= 0; --i) {
            node* splitStart = splits_[i];
            node* newNode = new node();
            newNode->value = newHead->value;
            newNode->prev = child;
            newNode->next = splitStart;
            splits_[i] = newNode;
            child = newNode;
        }
    }

    void insertSplit(node* newNode, size_t level) {
        if ((rand() % 100) < splitPct_) {
            node* lastSeen = lastSeenSplits_[level];
            node* newSplit = new node();
            newSplit->value = newNode->value;
            newSplit->next = lastSeen->next;
            lastSeen->next = newSplit;
            newSplit->prev = newNode;
            if (level > 0)
                insertSplit(newSplit, level - 1);
        }
    }

    void insertSplit(node* newNode) {
        insertSplit(newNode, splitCount_ - 1);
    }

    node* findInsertPointInSplits(const double& newNumber, node* prevStart, int splitIndex) {
        node* start = prevStart ? prevStart : splits_[splitIndex];

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
        const int splitCount_;
        const int splitPct_;
};