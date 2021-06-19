#include <iostream>
#include <assert.h>
#include <vector>
#include <omp.h>
#include <random>
#include <algorithm>

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

int test_scq_simple()
{
    int capacity = 10;
    SCQ scq(capacity);
    int valA = 1;
    int valB = 2;
    int retA = -1;
    int retB = -1;

    scq.enqueue(valA);
    retA = scq.dequeue();
    assert(valA == retA);
    retA = -1;


    scq.enqueue(valA);
    scq.enqueue(valB);


    retA = scq.dequeue();
    retB = scq.dequeue();

    assert(retA == valA);
    assert(retB == valB);

    return SUCCESS;
}

int test_scq_enqueu_dequeu_consecutive(int capacity, int threadCnt)
{
    // n threads enqueue in parallel. then  sync up and derqueue in parallel
    // once done we chack if every dequeued element is unique
    omp_set_num_threads(threadCnt);
    SCQ scq(capacity*1.2);

    #pragma omp parallel for
    for(int i = 0; i < capacity; i++)
    {
        scq.enqueue(i);
    }

    vector<int> dequeue_vals(capacity, -2);
    #pragma omp parallel for
    for(int i = 0; i < capacity; i++)
    {
        int val = scq.dequeue();
        dequeue_vals[val] = val;
    }

    int numn_errors = 0;
    #pragma omp parallel for    
    for(int i = 0; i < capacity; i++)
    {
        if(dequeue_vals[i] != i)
        {
            cout << "Values do not match on thread " << omp_get_thread_num() << endl;
            cout << "dequeue_vals[i]=" << dequeue_vals[i] << endl;
            cout << "i=" << i << endl;
            numn_errors++;         
        }
    }
    assert(numn_errors == 0);

    return SUCCESS;
}

int test_scq_enqueu_dequeu_mixed(int capacity, int threadCnt, int queue_ops)
{
    cout << "Testing SCQ mixed enqueuing/dequeuing" << endl;

    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};
    uniform_int_distribution<int> dist {1, 52};
    auto gen = [&dist, &mersenne_engine]()
    {           
        return dist(mersenne_engine); 
    };

    vector<int> initvals(queue_ops, -1);
    vector<int> retvals(queue_ops, -1);

    generate(begin(initvals), end(initvals), gen);

    //retvals = initvals; //have to check if equal in the end

    omp_set_num_threads(threadCnt);
    SCQ scq(capacity);

    #pragma omp parallel for
    for(int i = 0; i < queue_ops; i++)//=3)
    {
        scq.enqueue(initvals[i]);
        // scq.enqueue(initvals[i+1]);
        // scq.enqueue(initvals[i+2]);

        retvals[i] = scq.dequeue();
        // retvals[i+1] = scq.dequeue();
        // retvals[i+2] = scq.dequeue();
    }
    
    //#pragma omp barrier

    for(int i = 0; i < queue_ops; i++)
    {
        //cout << "i = " << i << ", initval = " << initvals[i] << ", retval = " << retvals[i] << endl;
        assert(initvals[i] == retvals[i] && "Values do not match!");
    }

    return SUCCESS;  
}


int main()
{
    cout << "Testing SCQ..." << endl;
    assert(test_scq_init() == SUCCESS);
    assert(test_scq_simple() == SUCCESS);
    

    assert(test_scq_enqueu_dequeu_consecutive(1000, 1) == SUCCESS);
    assert(test_scq_enqueu_dequeu_consecutive(1000, 10) == SUCCESS);
    assert(test_scq_enqueu_dequeu_consecutive(1000, 100) == SUCCESS);

    //assert(test_scq_enqueu_dequeu_mixed(512, 100, 1000) == SUCCESS); // TODO: Bernd

    cout << "All tests passed!" << endl;
}