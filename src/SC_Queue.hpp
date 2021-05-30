#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
#include <thread>
#include <atomic>

#include "common.h"


// CAS used for implementation
#define CAS(expected, desired) CAS_STD_ATOMIC_STRONG(expected, desired)

// possible CAS implementations
#define CAS_STD_ATOMIC_STRONG(expected, desired)  std::atomic::compare_exchange_strong(expected, desired)



// FAA uysed for implementaion
#define FAA(obj) FAA_STD_ATOMIC(obj)


// possible FAA implementations
#define FAA_STD_ATOMIC(obj) std::atomic_fetch_add(obj, 1);



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

        // Add an element to the queue
        void push(T x)
        {
            data[tail] = x;
            tail++;

            if(tail >= capacity)
            {
                tail = 0;
            }
        }
        // remove an element from the queue and return it
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

        // return the number of items currently in the queue
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

// SCQ implementation according to Figure 8 (p. 8)
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


