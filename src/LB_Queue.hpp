#pragma once
#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "common.h"

class LB_Queue
{
    private:
        mutable std::mutex m;
        std::vector<int>* items;
        int x;
        int capacity = 10;
        
    public:
        int head;
        int tail;
        //vector<double> T;
        vector<vector<int>> elements;

        LB_Queue()
        {
            head = 0;
            tail = 0;
            //items = (T)new Object[capacity];
            //items = new Object[capacity];
            //items = 
        }

        // Add an element to the queue.
        void push_back(int x) throw(int)
        {
            m.lock()

            try
            {
                if(tail - head == items.length)
                {
                    throw -1;
                } 

                items[tail % items.length] = x;
                tail++;
            }
            finally
            {
                m.unlock();
            }
        }

        pop_front() throw(int)
        {
            m.lock()

            try
            {
                if(tail == head)
                {
                    throw 0;
                } 

                x = items[head % items.length];

                head++;
                return x;
            }
            finally
            {
                m.unlock();
            }
        }

        // TODO: complete
        /*
        1 class LockBasedQueue<T> {
        2 int head, tail;
        3 T[] items;
        4 Lock lock;
        5 public LockBasedQueue(int capacity) {
        6 head = 0; tail = 0;
        7 lock = new ReentrantLock();
        8 items = (T[])new Object[capacity];
        9 }
        10 public void enq(T x) throws FullException {
        11 lock.lock();
        12 try {
        13 if (tail - head == items.length)
        14 throw new FullException();
        15 items[tail % items.length] = x;
        16 tail++;
        17 } finally {
        18 lock.unlock();
        19 }
        20 }
        21 public T deq() throws EmptyException {
        22 lock.lock();
        23 try {
        24 if (tail == head)
        25 throw new EmptyException();
        26 T x = items[head % items.length];
        27 head++;
        28 return x;
29 } finally {
30 lock.unlock();
31 }
32 }
33 }
*/  
};