#include "splitList.h"

class topFivePctContainer {
    public:
        topFivePctContainer(splitList& splits, const size_t size) : splits_(splits), fifthPctCounter_(1 + (size * 0.05)) {
            numbers_ = (node*)malloc(sizeof(node) * size);
        }

        ~topFivePctContainer() {
            free((void*)numbers_);
        }

        double getMarker() const {
            return fifthP_->value;
        }

        void insertFirst(double newNumber) {
            node* newNode = &numbers_[counter_];
            ++counter_;
            newNode->value = newNumber;
            head_ = newNode;
            fifthP_ = head_;
            splits_.updateNewHeadForSplits(head_);
        }

        void insertSecond(double newNumber) {
            node* newNode = &numbers_[counter_];
            ++counter_;
            newNode->value = newNumber;
            if (newNumber < head_->value) {
                tail_ = head_;
                tail_->prev = newNode;
                head_ = newNode;
                splits_.updateNewHeadForSplits(head_);
                newNode->next = tail_;
            } else {
                tail_ = newNode;
                tail_->prev = head_;
                head_->next = tail_;
            }
            fifthP_ = tail_;
        }        

        void maintainFifthP() {
            if ((counter_ - 1) % 20 == 0) {
                // must move fifthP back one to keep index;
                fifthP_ = fifthP_->prev;
            }
        }

        bool checkNewNumberAgainstMin(const double& newNumber) {
            if (fifthPCount_ == nullptr) {
                if (counter_ == fifthPctCounter_) {
                    fifthPCount_ = head_;
                }
            } else {
                if (fifthPCount_->value >= newNumber) {
                    ++counter_;
                    maintainFifthP();
                    return false;
                }
            }
            return true;
        }

        void insertNumber(double newNumber) {
            if (!checkNewNumberAgainstMin(newNumber))
                return;

            node* newNode = &numbers_[counter_++];
            newNode->value = newNumber;

            // find where to insert
            if (newNumber <= head_->value) {
                newNode->next = head_;
                head_->prev = newNode;
                head_ = newNode;
                splits_.updateNewHeadForSplits(head_);
            } else {
                node* checkAgainst = splits_.findInsertPointInSplits(newNumber);

                while (checkAgainst->next && newNumber > checkAgainst->value) {
                    checkAgainst = checkAgainst->next;
                }

                if (!checkAgainst->next && newNumber > checkAgainst->value) {
                    // new tail
                    tail_->next = newNode;
                    newNode->prev = tail_;
                    tail_ = newNode;
                } else {
                    // insert before checkAgainst
                    newNode->next = checkAgainst;
                    newNode->prev = checkAgainst->prev;
                    checkAgainst->prev = newNode;
                    newNode->prev->next = newNode;
                }
                splits_.insertSplit(newNode, counter_);
            }

            if (newNumber > fifthP_->value) {
                // must move fifthP forward one to keep index;
                fifthP_ = fifthP_->next;
            }

            if (fifthPCount_ && fifthPCount_->next) {
                fifthPCount_ = fifthPCount_->next;
            }

            maintainFifthP();
        }

    private:
        splitList& splits_;

    public:
        node* numbers_ = nullptr;
        node* fifthP_ = nullptr;
        node* fifthPCount_ = nullptr;
        node* head_ = nullptr;
        node* tail_ = nullptr;
        size_t counter_ = 0;
        const size_t fifthPctCounter_;

};