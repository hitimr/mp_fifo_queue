#pragma once
#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <assert.h>

#include "common.h"

class LB_Queue
{
    private:
        size_t m_capacity = 0;
        size_t m_size = 0;

    public:    
        std::string name = "LockBased Queue";
        size_t head, tail;
        std::vector<std::vector<int> *> items;
        std::mutex * lock;
        
        int capacity = 10;
        
        LB_Queue(size_t capacity) : m_capacity(capacity)
        {
            lock = new std::mutex();


            head = 0;
            tail = 0;
            m_size = 0;

            items.clear();
            items.resize(capacity);
        }

        size_t size() { return m_size; }
        bool empty() { return m_size == 0 ? true : false; }

        // Add an element to the queue.
        int enqueue(std::vector<int> * x)
        {        
            if(m_size == m_capacity)
            {
                return ERROR_QUEUE_FULL;
            } 
            
            lock->lock();

            items[tail % items.size()] = x;
            tail++;
            m_size++;

            lock->unlock();
            return SUCCESS;
        }

        std::vector<int> * dequeue()
        {
            lock->lock();

            if(tail == head)
            {
                return NULL;
            } 

            auto element = items[head % items.size()];
            head++; 
            m_size--;       

            lock->unlock();

            return element;
        }
};