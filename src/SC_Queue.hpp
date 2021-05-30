#pragma once
#include <iostream>
#include <assert.h>
#include <vector>

#include "common.h"


template <class T>
class RingBuffer
{
    size_t capacity, head, tail;
    std::vector<T> data;

    public:
        RingBuffer(size_t new_capacity)
        {
            assert(new_capacity > 0);

            capacity = new_capacity;
            head = 0;
            tail = 0;

            data.clear();
            data.resize(capacity);
        }

        void push(T x)
        {
            data[tail] = x;
            tail++;

            if(tail >= capacity)
            {
                tail = 0;
            }
        }

        T pop()
        {
            T x = data[head];
            head++;
            if(head >= capacity)
            {
                head = 0;
            }
            return x;
        }

        size_t size()
        {
            if(head <= tail)
            {
                return tail - head;
            }
            else
            {
                return head - tail;
            }
        }

        void clear()
        {
            head = 0;
            tail = 0;
        }
};

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