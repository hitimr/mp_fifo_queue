#pragma once
#include <queue>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace chrono;

class Benchmarker
{
    public:
        // benchmark setup
        int m_threadcnt = -1;
        int m_object_count = -1;
        int m_object_size = -1;
        vector<vector<int>> m_objects;
        int m_repeats = -1;
        

        // results
        string m_queue_name = "noName";
        std::vector<double> m_enqueue_times;
        std::vector<double> m_enqueue_rates;

        void initialize(int thread_cnt, int object_cnt, int object_size, int repeats);
        void printResults();
        template<class queue_t> void benchmark(queue_t & q);
        template<class queue_t> void benchmark_enqueu(queue_t & q);
};



template<class queue_t> void Benchmarker::benchmark(queue_t & q)
{
    m_queue_name = q.name;
    for(int i = 0; i < m_repeats; i++)
    {
        benchmark_enqueu(q);
    }
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
    double enqueue_time = duration<double, std::milli>(end-start).count();
    m_enqueue_times.push_back(enqueue_time);
    m_enqueue_rates.push_back((double) m_object_count / enqueue_time);
}