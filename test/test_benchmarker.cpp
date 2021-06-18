#include <iostream>
#include <assert.h>
#include <vector>
#include <omp.h>

#include "SCQ.hpp"
#include "common.h"
#include "LB_Queue.hpp"
#include "benchmark.hpp"

using namespace std;




int main()
{
    cout << "Testing Benchmarker..." << endl;

    int capacity = 1e6;
    Benchmarker benchmarker;    
    benchmarker.initialize(8, capacity, 10, 10);

    FIFO_Queue fifo_q(capacity);
    LB_Queue lb_q(capacity);

    benchmarker.benchmark<FIFO_Queue>(fifo_q);
    benchmarker.benchmark<LB_Queue>(lb_q);

    cout << "All tests for FIFO queue passed!" << endl;

    return SUCCESS;
}
