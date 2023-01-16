#pragma once

#include "node.h"
#include "stdlib.h"
#include <vector>
#include <cstddef>
#include <math.h>
#include <stdexcept>
#include <iostream>

class nodeAllocator {
    public:
        nodeAllocator(size_t size) : size_(size) {
            node* chunk = (node*)malloc(sizeof(node) * size);
            LeafChunks_.push_back(chunk);
            activeLeafChunk_ = chunk;

            chunk = (node*)malloc(sizeof(node) * size);
            SplitChunks_.push_back(chunk);
            activeSplitChunk_ = chunk;
        }

        node* getLeafNode() {
            if (leafCounter_ == size_) {
                std::cout << "Allocating more memory\n";
                // must allocate more memory
                node* chunk = (node*)malloc(sizeof(node) * size_);
                LeafChunks_.push_back(chunk);
                activeLeafChunk_ = chunk;
                leafCounter_ = 0;
            }
            node* returnNode = activeLeafChunk_ + leafCounter_;
            ++leafCounter_;
            return returnNode;
        }

        node* getSplitNode() {
            if (splitCounter_ == size_) {
                std::cout << "Allocating more memory\n";
                // must allocate more memory
                node* chunk = (node*)malloc(sizeof(node) * size_);
                SplitChunks_.push_back(chunk);
                activeSplitChunk_ = chunk;
                splitCounter_ = 0;
            }
            node* returnNode = activeSplitChunk_ + splitCounter_;
            ++splitCounter_;
            return returnNode;
        }

        ~nodeAllocator() {
            for (node* n : LeafChunks_) {
                free(n);
            }
            for (node* n : SplitChunks_) {
                free(n);
            }
        }

    private:
        size_t leafCounter_ = 0;
        size_t splitCounter_ = 0;
        size_t size_;
        std::vector<node*> LeafChunks_;
        std::vector<node*> SplitChunks_;
        node* activeLeafChunk_;
        node* activeSplitChunk_;
};