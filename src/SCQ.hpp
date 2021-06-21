#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
#include <thread>
#include <atomic>
#include <string>

#include "common.h"


// CAS used for implementation
#define CAS(location, expected, desired) CAS_STD_ATOMIC_STRONG(location, expected, desired)


// possible CAS implementations
#define CAS_STD_ATOMIC_STRONG(location, expected, desired)  std::atomic::compare_exchange_strong(location, expected, desired)



// FAA uysed for implementaion
#define FAA(obj, n) FAA_STD_ATOMIC(obj, n)


// possible FAA implementations
// https://en.cppreference.com/w/cpp/atomic/atomic_fetch_add
#define FAA_STD_ATOMIC(obj, n) std::atomic_fetch_add(obj, n);


// used in earlier stages of development
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
        const size_t m_capacity;
        
        std::atomic<size_t> head;
        std::atomic<size_t> tail;
        std::atomic<int> threshold;
        std::atomic<SCQ_Element> * entries;

        SCQ(size_t new_capacity);
        // TODO: destructor

        void enqueue(int index);
        int dequeue();
        size_t capacity() const { return m_capacity; }
        // TODO: size
          
    private:
        void catchup(size_t t, int h); 
        size_t cache_remap(const std::atomic<size_t> & idx)
        {
            return idx % ((int)1.5*m_capacity);
            //return idx; // TODO: fix cache_remaps
            // from https://github.com/rusnikola/lfqueue/blob/master/lfring_cas1.h
            //return (size_t) (idx & (n - 1));    // TODO: understand WTF is going on here
        }
};

class FIFO_Queue
{
    public:
        size_t m_capacity;
        std::vector<int> ** m_data;
        std::atomic<int> m_size;

        SCQ * aq;
        SCQ * fq;
    
        std::string name = "FIFO Queue";
        FIFO_Queue(size_t capacity);
        ~FIFO_Queue();

        int enqueue(std::vector<int> * obj);
        std::vector<int> * dequeue();
        size_t capacity() { return m_capacity; }
        bool empty() { return m_size == 0 ? true : false;  }    // WARNING: testing has shown this routine is not thread safe
        size_t size() { return m_size; }
};


