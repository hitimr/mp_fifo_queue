#include <iostream>
#include <omp.h>
#include <string>
#include <fstream>

#include "benchmark.hpp"
#include "common.h"

using namespace std;


void Benchmarker::initialize(int thread_cnt, int object_cnt, int object_size, int repeats = 1) 
{ 
    m_threadcnt = thread_cnt;     
    m_object_count = object_cnt;
    m_object_size = object_size;
    m_repeats = repeats;

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

void Benchmarker::write_results_to_file()
{
    string fileName = "measurements/" + 
        m_queue_name + "_" + 
        to_string(m_threadcnt) + "_" + 
        to_string(m_object_count) + 
        ".csv";
        
    ofstream outfile(fileName);
    
    outfile << "queue name;run id;thread count;object count;object size;total enqueue time;total dequeue time;enqueue rate;dequeue rate"  << endl;
    for(int i = 0; i < m_repeats; i++)
    {
        outfile << 
            m_queue_name << ";" << 
            i+1 << ";" <<
            m_threadcnt << ";" << 
            m_object_count << ";" << 
            m_object_size << ";" <<
            m_enqueue_times[i] << ";" << 
            m_dequeue_times[i] << ";" << 
            m_enqueue_rates[i] << ";" << 
            m_dequeue_rates[i] << 
            endl;
    }
    outfile.close();
}


void Benchmarker::printResults()
{
    cout << "Finished evaluating " << m_queue_name << endl;

    cout << "average total Enqueue time [ms] = " << average(m_enqueue_times) << endl;
    cout << "average enqueues/s [1/ms] = " << average(m_enqueue_rates) << endl;
    cout << "average time per enqueue [ns] = " << 1.0/average(m_enqueue_rates)*1000 << endl;

    cout << "average total Dequeue time [ms] = " << average(m_dequeue_times) << endl;
    cout << "average dequeues/s [1/ms] = " << average(m_dequeue_rates) << endl;
    cout << "average time per dequeue [ns] = " << 1.0/average(m_dequeue_rates)*1000.0 << endl;
    cout << endl;
}
