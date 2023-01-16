#include "node.h"
#include <vector>
#include <cstddef>
#include <cstdlib>

class dumbContainer {
    public:
        dumbContainer(const size_t size) : fifthPctCounter_(1 + (size * 0.05)) {
            numbers_ = (node*)malloc(sizeof(node) * size);
        }

        // iterate through whole list, don't use tail or prev
        void insertNumberIterating(double newNumber) {
            node* lclHead = head_;
            node* newNode = &numbers_[counter_++];
            newNode->value = newNumber;
            while (lclHead->next){
                lclHead = lclHead->next;
            }
            lclHead->next = newNode;
        }

        void insertAtTail(double newNumber) {
            node* newNode = &numbers_[counter_++];
            newNode->value = newNumber;
            tail_->next = newNode;
            tail_ = newNode;
        }

        void insertFirst(double newNumber) {
            node* newNode = &numbers_[counter_];
            ++counter_;
            newNode->value = newNumber;
            head_ = newNode;
            tail_ = head_;
        }

    public:
        node* numbers_ = nullptr;
        node* head_ = nullptr;
        node* tail_ = nullptr;
        size_t counter_ = 0;
        const size_t fifthPctCounter_;
};