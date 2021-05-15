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
    //LB_Queue lb_queue = LB_Queue();
    //cout << "Hi from Bernd!" << endl;
}

int main()
{
    //playground_bernd();
    playground_hiti();
}