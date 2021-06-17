#include <iostream>
#include <assert.h>
#include <vector>
#include <omp.h>

#include "SCQ.hpp"
#include "common.h"


using namespace std;

int test_scq_init()
{
    cout << "Testing SCQ Constructur" << endl;
    
    { 
        SCQ scq(10); 
        assert(scq.capacity() == 10);
    }

    { 
        SCQ scq((int) 1e7); 
        assert(scq.capacity() == (int) 1e7);
    }    
    
    return SUCCESS;
}

int test_scq_enqueu_dequeu_consecutive(int capacity, int threadCnt)
{
    // n threads enqueue in parallel. then  sync up and derqueue in parallel
    // once done we chack if every dequeued element is unique
    omp_set_num_threads(threadCnt);
    SCQ scq(capacity);

    #pragma omp parallel for
    for(int i = 0; i < capacity; i++)
    {
        scq.enqueue(i);
    }
    #pragma omp barrier

    vector<int> dequeue_vals(capacity, -1);
    #pragma omp parallel for
    for(int i = 0; i < capacity; i++)
    {
        int val = scq.dequeue();
        dequeue_vals[val] = val;
    }

    for(int i = 0; i < capacity; i++)
    {
        assert(dequeue_vals[i] == i);
    }

    return SUCCESS;
}

int test_scq_enqueu_dequeu_mixed(int capacity, int threadCnt, int queue_ops)
{
    return SUCCESS;  
}


int main()
{
    assert(test_scq_init() == SUCCESS);

    std::cout << "Testing enqueue/dequeue" << std::endl;
    assert(test_scq_enqueu_dequeu_consecutive(1000, 1) == SUCCESS);
    assert(test_scq_enqueu_dequeu_consecutive(1000, 10) == SUCCESS);
    assert(test_scq_enqueu_dequeu_consecutive(1000, 100) == SUCCESS);

    //assert(test_scq_enqueu_dequeu_consetest_scq_enqueu_dequeu_mixedcutive(1000, 2, 100) == SUCCESS); // TODO: Bernd
}