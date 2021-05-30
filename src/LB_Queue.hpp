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
    public:
        size_t head, tail;
        std::vector<queue_element*> items;
        std::mutex * lock;
        
        int x;
        int capacity = 10;
        
        LB_Queue(std::mutex * new_lock)
        {
            // TODO variable size
            capacity = 10;
            //ssert(capacity > 0);
            lock = new_lock;


            head = 0;
            tail = 0;
            //capacity = new_capacity;

            items.clear();
            items.resize(capacity);
        }

        // Add an element to the queue.
        int push(queue_element & x)
        {
            lock->lock();

            if(tail - head == items.size())
            {
                return ERROR_QUEUE_FULL;
            } 

            items[tail % items.size()] = &x;
            tail++;

            lock->unlock();
            return SUCCESS;
        }

        queue_element* pop()
        {
            lock->lock();

            if(tail == head)
            {
                return NULL;
            } 

            auto element = items[head % items.size()];
            head++;        

            lock->unlock();
            return element;
        }
};