#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
#include <thread>
#include <atomic>

#include "common.h"


// CAS used for implementation
#define CAS(location, expected, desired) CAS_STD_ATOMIC_STRONG(location, expected, desired)


// possible CAS implementations
#define CAS_STD_ATOMIC_STRONG(location, expected, desired)  std::atomic::compare_exchange_strong(location, expected, desired)



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
    size_t cycle;
    bool isSafe;
    int index;
} SCQ_Element;


// SCQ implementation according to Figure 8 (p. 8)
class SCQ
{
    public:
        const size_t capacity;
        
        std::atomic<size_t> head;
        std::atomic<size_t> tail;
        std::atomic<int> threshold;
        std::atomic<SCQ_Element> * entries;

        SCQ(size_t new_capacity);
        void enqueue(int index);
        int dequeue();

        
        


    private:
        size_t cache_remap(const std::atomic<size_t> & idx, size_t n)
        {
            // from https://github.com/rusnikola/lfqueue/blob/master/lfring_cas1.h
            return (size_t) (idx & (n - 1));    // TODO: understand WTF is going on here
        }
};


