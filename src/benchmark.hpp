#pragma once
#include <queue>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace chrono;

class Benchmarker
{
    private:
        // benchmark setup
        int m_threadcnt = -1;
        int m_object_count = -1;
        int m_object_size = -1;
        vector<vector<int>> m_objects;
        
        // results
        string m_queue_name = "noName";
        double m_enqueue_time = -1;
        double m_enqueue_rate = -1;

    public:
        void initialize(int thread_cnt, int object_cnt, int object_size);
        void printResults();
        template<class queue_t> void benchmark(queue_t & q);
        template<class queue_t> void benchmark_enqueu(queue_t & q);
};



template<class queue_t> void Benchmarker::benchmark(queue_t & q)
{
    m_queue_name = q.name;
    benchmark_enqueu(q);
    printResults();
}

// For some reason I cant put that into a source file...
template<class queue_t> void Benchmarker::benchmark_enqueu(queue_t & q)
{
    auto start = std::chrono:: high_resolution_clock::now();

    // enqueue all objects
    #pragma omp parallel for
    for(int i = 0; i < m_object_count; i++)
    {
        q.enqueue(&m_objects[i]);
    }

    auto end = high_resolution_clock::now();
    m_enqueue_time = duration<double, std::milli>(end-start).count();
    m_enqueue_rate = (double) m_object_count / m_enqueue_time;
}