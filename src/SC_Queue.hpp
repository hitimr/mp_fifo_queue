#pragma once
#include <iostream>
#include <assert.h>
#include <vector>

#include "common.h"


typedef struct SCQ_Element_t
{
    int cycle;
    bool isSafe;
    int index;
} SCQ_Element;

class SC_Queue
{
    public:
        size_t tail, head, capacity;
        int threshold = -1;

        std::vector<SCQ_Element> entries;

        SC_Queue(size_t new_capacity)
        {
            assert(new_capacity > 0);

            capacity = new_capacity;
            tail = 2 * capacity;
            head = 2* capacity;
            
            entries.clear();
            entries.resize(2*capacity, {0, true, INITIAL_INDEX});  // Line 4
        }
};