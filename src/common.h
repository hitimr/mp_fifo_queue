#pragma once
#include <string>

#define SUCCESS 0
#define ERROR_QUEUE_FULL -1
#define ERROR_QUEUE_EMPTY -2

// Initial values for an SCQ Element according to Fig 8, Line 4
#define INITIAL_ENTRY_CYCLE 0
#define INITIAL_ENTRY_ISSAFE true
#define INITIAL_ENTRY_INDEX -1

// sequential consistent memory order required according to paper Section 3 (assumptions)
#define MEMORY_ORDER std::memory_order_seq_cst



typedef std::string queue_element;
