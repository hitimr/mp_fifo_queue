#pragma once
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

class Benchmarker
{
    public:
        template<class queue_t> void benchmark(queue_t & q);
};



// For some reason I cant put that into a source file...
template<class queue_t> void Benchmarker::benchmark(queue_t & q)
{
    // gnerate objects
    int object_count = 1e7;
    int object_size = 10;
    vector<vector<int>> objects(object_count);
    
    for(int i = 0; i < object_count; i++)
    {
        vector<int> new_obj(object_size, i);
        objects[i] = new_obj;
    }



    auto start = std::chrono:: high_resolution_clock::now();

    // enqueue all objects
    for(int i = 0; i < object_count; i++)
    {
        q.enqueue(&objects[i]);
    }


    // dequeue all objects
    while(!q.empty())
    {
        q.dequeue();
    }

    auto end = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(end-start).count()  << std::endl;

}
