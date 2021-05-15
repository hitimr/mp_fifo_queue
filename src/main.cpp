#include <iostream>
#include "LB_Queue.hpp"
#include "benchmark.hpp"
#include <queue>

using namespace std;



template<class queue_t>
void benchmark(queue_t q)
{
    q.size();
}



void playground_hiti()
{
    queue<int> a;
    benchmark<queue<int>>(a);
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