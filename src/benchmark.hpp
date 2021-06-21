#pragma once
#include <queue>
#include <chrono>
#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>

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
        std::vector<double> m_dequeue_times;
        std::vector<double> m_enqueue_rates;
        std::vector<double> m_dequeue_rates;
        std::vector<double> m_pair_time;

        void initialize(int thread_cnt, int object_cnt, int object_size, int repeats);
        void printResults();
        void write_results_to_file();
        template<class queue_t> void benchmark(queue_t & q);
        template<class queue_t> void benchmark_enqueu(queue_t & q);
        template<class queue_t> void benchmark_dequeue(queue_t & q);
};


// For some reason I cant put template methods into a source file...
template<class queue_t> void Benchmarker::benchmark(queue_t & q)
{
    m_enqueue_times.clear();
    m_dequeue_times.clear();
    m_enqueue_rates.clear();
    m_dequeue_rates.clear();
    m_pair_time.clear();

    m_queue_name = q.name;
    for(int i = 0; i < m_repeats; i++)
    {
        benchmark_enqueu(q);
        benchmark_dequeue(q);
    }
    printResults();
    write_results_to_file();
}


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

template<class queue_t> void Benchmarker::benchmark_dequeue(queue_t & q)
{
    std::vector<std::vector<int>*> dequeued_ptrs(m_object_count);
    auto start = std::chrono:: high_resolution_clock::now();
    // enqueue all objects
    #pragma omp parallel for
    for(int i = 0; i < m_object_count; i++)
    {
        dequeued_ptrs[i] = q.dequeue();
    }
    auto end = high_resolution_clock::now();

    
    // check results
    assert(q.empty() == true);    
    for(int j = 0; j < m_object_size; j++)
    {
        vector<int> values_to_check(m_object_count, -1);
        for(int i = 0; i < m_object_count; i++) 
        {
            int val = dequeued_ptrs.at(i)->at(j);
            values_to_check[val] = val;
        }
        // compare values 
        for(int i = 0; i < m_object_count; i++)
        {
            assert(values_to_check[i] == i && "Values in queue dont match");
        } 
    }


    double dequeue_time = duration<double, std::milli>(end-start).count();
    m_dequeue_times.push_back(dequeue_time);
    m_dequeue_rates.push_back((double) m_object_count / (dequeue_time * m_threadcnt));
}