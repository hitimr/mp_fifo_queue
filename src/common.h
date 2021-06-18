#pragma once
#include <string>

#define SUCCESS 0
#define ERROR_QUEUE_EMPTY -1
#define ERROR_QUEUE_FULL -2


// Initial values for an SCQ Element according to Fig 8, Line 4
#define INITIAL_ENTRY_CYCLE 0
#define INITIAL_ENTRY_ISSAFE true
#define INITIAL_ENTRY_INDEX -1

// sequential consistent memory order required according to paper Section 3 (assumptions)
#define MEMORY_ORDER std::memory_order_seq_cst



typedef std::string queue_element;

inline double average(std::vector<double> & vec)
{
    double avg = 0;
    for(size_t i = 0; i < vec.size(); i++)
    {
        avg += vec[i];
    } 
    return avg / ((double) vec.size());
}
