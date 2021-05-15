#pragma once
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

class Benchmarker
{
    public:
        template<class queue_t> void benchmark(queue_t q);
};



// For some reason I cant put that into a source file...
template<class queue_t> void Benchmarker::benchmark(queue_t q)
{
    auto start = std::chrono:: high_resolution_clock::now();
    for(int i = 0; i < 10000; i++)
    {
        q.push(i);
    }

    while(!q.empty())
    {
        q.pop();
    }
    auto end = high_resolution_clock::now();
    cout << duration<double, std::milli>(end-start).count()  << endl;

}
