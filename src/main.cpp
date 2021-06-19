#include <iostream>
#include <queue>
#include <string>

#include "LB_Queue.hpp"
#include "SCQ.hpp"
#include "benchmark.hpp"

using namespace std;





void playground_hiti()
{

    int capacity = 1e4;
    Benchmarker benchmarker;    
    benchmarker.initialize(16, capacity, 10, 2);
    
    FIFO_Queue fifo_q(capacity);
    LB_Queue lb_q(capacity);
    
    benchmarker.benchmark<FIFO_Queue>(fifo_q);
    //benchmarker.benchmark<LB_Queue>(lb_q);

    return;
}

/* CLI arguments: 

[queue_type]    FIFO or LB
[num_objects]   number of objects that should get enqueued
[object_size]   size of objects. does not really matter since we are enqueuing pointers to said objects
[num_threads]   number of threads for ther benchmarking
[repeats]       number of times the benchmark is repeated. results are logged individually

*/
int main(int argc, char *argv[])
{
    string queue_type;
    int num_threads;
    int num_objects;
    int object_size;
    int repeats;
    int capacity;

    // parse CLI argumments
    if(argc == 6)
    {
        queue_type = string(argv[ARG_QUEUE_TYPE]);
        num_threads = stoi(argv[ARG_NUM_THREADS]);
        num_objects = stoi(argv[ARG_NUM_OBJECTS]);
        object_size = stoi(argv[ARG_OBJECT_SIZE]);
        repeats = stoi(argv[ARG_REPEATS]);
        capacity = 1.2*num_objects;
    }
    else if(argc == 1)
    {
        queue_type = "FIFO",
        num_threads = 4;
        num_objects = 10000;
        object_size = 1;
        repeats = 10;
        capacity = 1.2*num_objects;
    }


    // some checks..
    assert(num_threads > 0);
    assert(num_objects > 0);
    assert(object_size >= 0);  // empty objects are valid
    assert(repeats > 0);

    // setup benchmarker
    Benchmarker benchmarker;    
    benchmarker.initialize(
        num_threads, 
        num_objects, 
        object_size, 
        repeats
        );


    if(queue_type == "FIFO")
    {
        FIFO_Queue fifo_q(capacity);
        LB_Queue lb_q(capacity);

        benchmarker.benchmark<FIFO_Queue>(fifo_q);
    }
    else if (queue_type == "LB")
    {
        assert(false && "LB queue benchmark coming soon (tm)");
        // TODO LB queue benchmark
    }
    else
    {
        cout << "Error: invalid queue type" << endl;
    }     
}

