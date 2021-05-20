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
    //cout << "Hi from Bernd!" << endl;
}

int main()
{
    playground_bernd();
    //playground_hiti();
}