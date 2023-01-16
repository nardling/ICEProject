#pragma once

struct node {
    // make this a union
    node* prev = nullptr;
    node* next = nullptr;
    double value;
};