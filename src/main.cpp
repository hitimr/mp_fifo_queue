#include <iostream>
#include "LB_Queue.hpp"
#include "SCQ.hpp"
#include "benchmark.hpp"
#include <queue>

using namespace std;





void playground_hiti()
{

    int capacity = 1e6;
    Benchmarker benchmarker;    
    benchmarker.initialize(8, capacity, 10, 10);
    
    FIFO_Queue fifo_q(capacity);
    LB_Queue lb_q(capacity);
    
    benchmarker.benchmark<FIFO_Queue>(fifo_q);
    benchmarker.benchmark<LB_Queue>(lb_q);

    return;
}

void playground_bernd()
{
    // mutex lock;
    // LB_Queue lb_queue = LB_Queue(&lock);

    // queue_element a = "hello";
    // queue_element b = "world";

    // lb_queue.push(a);
    // lb_queue.push(b);

    // cout << (*lb_queue.pop()) << endl;
    // cout << (*lb_queue.pop()) << endl;
    // void test_Q_functionality()
    // {
        

    //     return SUCCESS;
    // }
}

int main()
{
    //playground_bernd();
    playground_hiti();
    cout << "Done" << endl;
}