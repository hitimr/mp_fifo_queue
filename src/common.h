#pragma once
#include <string>

#define SUCCESS 0
#define ERROR_QUEUE_FULL -1
#define ERROR_QUEUE_EMPTY -2

// Initial values for an SCQ Element according to Fig 8, Line 4
#define INITIAL_ENTRY_CYCLE 0
#define INITIAL_ENTRY_ISSAFE 1
#define INITIAL_ENTRY_INDEX -1


#define MEMORY_ORDER std::memory_order_relaxed



typedef std::string queue_element;
