#include <iostream>
#include "LB_Queue.hpp"
#include "SCQ.hpp"
#include "benchmark.hpp"
#include <queue>

using namespace std;





void playground_hiti()
{
    /*
    Benchmarker benchmarker;

    queue<int> a;
    benchmarker.benchmark<queue<int>>(a);
    */
   
    int n = 1000;
    SCQ scq(n);
    for(int i = 0; i < n; i++)
    {
        scq.enqueue(i);
    }

    vector<int> test(n);
    for(int i = 0; i < n; i++)
    {
        test[i] = scq.dequeue();
    }

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
}

int main()
{
    //playground_bernd();
    playground_hiti();
    cout << "Done" << endl;
}