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
// https://en.cppreference.com/w/cpp/atomic/atomic_fetch_add
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
            //std::cout << capacity << ", " << size() << std::endl;
            //assert(size() < capacity && "buffer full!");            

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

        size_t max_size()
        {
            return capacity;
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
        size_t head, capacity;
        std::atomic<size_t> tail;
        int threshold = -1;

        std::vector<std::atomic<SCQ_Element>> entries;

        SC_Queue(size_t new_capacity)
        {
            assert(new_capacity > 0);

            capacity = new_capacity;
            tail = 2 * capacity;
            head = 2 * capacity;
            /*
            entries.clear();
            entries.resize(2*capacity);  // Line 4   

            for(auto itr = entries.begin(); itr < entries.end(); itr++)
            {
                *itr = {0, false, 0};
            }      */
        }

        void enqueue(int index)
        {
            while(true)
            {
                size_t T = FAA(&tail);
                size_t j = cache_remap(T % capacity, capacity);
                //SCQ_Element ent = entries[j].load(std::memory_order_relaxed);
            }
        }


    private:
        size_t cache_remap(const std::atomic<size_t> & idx, size_t n)
        {
            // from https://github.com/rusnikola/lfqueue/blob/master/lfring_cas1.h
            return (size_t) (idx & (n - 1));    // TODO: understand WTF is going on here
        }
};


