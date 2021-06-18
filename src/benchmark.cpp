#include <iostream>
#include <omp.h>
#include "benchmark.hpp"

using namespace std;


void Benchmarker::initialize(int thread_cnt, int object_cnt, int object_size) 
{ 
    m_threadcnt = thread_cnt;     
    m_object_count = object_cnt;
    m_object_size = object_size;

    // gnerate objects. use max threads for faster execution
    omp_set_num_threads(omp_get_max_threads());
    m_objects.clear();
    m_objects.resize(m_object_count);    
    #pragma omp parallel for
    for(int i = 0; i < m_object_count; i++)
    {
        vector<int> new_obj(m_object_size, i);
        m_objects[i] = new_obj;
    }
    omp_set_num_threads(m_threadcnt);

    return;
}


void Benchmarker::printResults()
{
    cout << "Finished evaluating " << m_queue_name << endl;
    cout << "Total Enqueue time [ms] = " << m_enqueue_time << endl;
    cout << "Enqueues/s [1/ms] = " << m_enqueue_rate << endl;
    cout << endl;
}


