#include <iostream>
#include <assert.h>
#include <vector>
#include <omp.h>

#include "SCQ.hpp"
#include "common.h"


using namespace std;


int test_enqueue_dequeue()
{
    size_t n = 100;
    size_t vec_size = 10;
    FIFO_Queue q(n);
    vector<int> obj_A(vec_size, 1);
    vector<int> obj_B(vec_size, -1);
     

    assert(q.empty() == true);
    q.enqueue(&obj_A);
    assert(q.size() == 1);
    q.enqueue(&obj_B);
    assert(q.size() == 2);
    assert(q.empty() == false);

    vector<int> * ptr_A = q.dequeue();
    vector<int> * ptr_B = q.dequeue();
    assert(q.size() == 0);
    assert(q.empty() == true);

    for(size_t i = 0; i < vec_size; i++)
    {
        assert(ptr_A->at(i) == 1);
        assert(ptr_B->at(i) == -1);
    }
    assert(q.size() == 0);
    assert(q.empty() == true);

    return SUCCESS; 
}


int test_constructor()
{
    size_t size = 10;
    FIFO_Queue q(size);
    assert(q.capacity() == size);
    assert(q.size() == 0);

    vector<int> obj;
    q.enqueue(&obj);
    assert(q.size() == 1);

    return SUCCESS;
}




int main()
{
    cout << "Testing FIFO queue..." << endl;

    assert(test_enqueue_dequeue() == SUCCESS);
    assert(test_constructor() == SUCCESS);

    cout << "All tests for FIFO queue passed!" << endl;
}