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

int test_fifo_wraparound(int threadCnt)
{
    // queue is filled to 70% and then emptied again. this priocess is repeated several times
    // some values i.e. tail of an SCQ wil wrap around during the second repeat
    int capacity = 1000;
    int repeats = 10;
    int num_objects = (int) capacity*0.7;
    FIFO_Queue q(capacity);
    omp_set_num_threads(threadCnt);


    vector<vector<int>> objects;
    vector<vector<int> *> dequeued_elements(num_objects);
    for(int i = 0; i < (int) num_objects; i++)
    {
        vector<int> new_object(1, i);
        objects.push_back(new_object);
    }    


    for(int r = 0; r < repeats; r++)
    {
        #pragma omp parallel for
        for(int i = 0; i < num_objects; i++)
        {
            q.enqueue(&objects[i]);
        }
     
        #pragma omp parallel for
        for(int i = 0; i < num_objects; i++)
        {
            vector<int> * dq_element = q.dequeue();
            dequeued_elements[dq_element->at(0)] = dq_element;
        }

        for(int i = 0; i < num_objects; i++)
        {
            assert(dequeued_elements[i]->at(0) == i);
        }
        assert(q.empty() == true);

    }
    
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

    cout << "Testing wraparound correctness of FIFO queue..." << endl;
    assert(test_fifo_wraparound(1) == SUCCESS);
    assert(test_fifo_wraparound(10) == SUCCESS);
    assert(test_fifo_wraparound(100) == SUCCESS);
    cout << "Done" << endl;

    cout << "All tests for FIFO queue passed!" << endl;
}