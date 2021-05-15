#pragma once
#include <queue>

class Benchmarker
{
    public:
        template<class queue_t> void benchmark(queue_t q);
};



// For some reason I cant put that into a source file...
template<class queue_t> void Benchmarker::benchmark(queue_t q)
{
    q.size();
}
