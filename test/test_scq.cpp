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

int test_scq_enqueu_dequeu()
{
    {
        int capacity = 10;
        SCQ scq(capacity);
        scq.enqueue(1);
        assert(scq.dequeue() == 1);
        assert(scq.dequeue() == ERROR_QUEUE_EMPTY);
    }

    
    {
        int capacity = 1e3;
        int threadeCnt = 1;
        omp_set_num_threads(threadeCnt);
        SCQ scq(capacity);

        // generate lots of values to enqueue
        vector<int> enqueue_vals(capacity);
        for(size_t i = 0; i < enqueue_vals.size(); i++)
        {
            enqueue_vals[i] = i;
        }

        #pragma omp parallel for
        for(int i = 0; i < capacity; i++)
        {
            scq.enqueue(enqueue_vals[i]);
        }
        #pragma omp barrier

        vector<int> dequeue_vals(capacity);
        #pragma omp parallel for
        for(int i = 0; i < capacity; i++)
        {
            int val = scq.dequeue();
            dequeue_vals[i] = val;
        }
        #pragma omp barrier
        return 0;
    }
    


    return SUCCESS;
}



int main()
{
    assert(test_scq_init() == SUCCESS);
    assert(test_scq_enqueu_dequeu() == SUCCESS);
}