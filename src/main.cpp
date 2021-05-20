#include <iostream>
#include "LB_Queue.hpp"
#include "benchmark.hpp"
#include <queue>

using namespace std;





void playground_hiti()
{
    Benchmarker benchmarker;

    queue<int> a;
    benchmarker.benchmark<queue<int>>(a);
}

void playground_bernd()
{
    mutex lock;
    LB_Queue lb_queue = LB_Queue(&lock);

    queue_element a = "hello";
    queue_element b = "world";

    lb_queue.push_back(a);
    lb_queue.push_back(b);

    cout << (*lb_queue.pop_front()) << endl;
    cout << lb_queue.pop_front() << endl;
}

int main()
{
    playground_bernd();
    //playground_hiti();
}