#include "SCQ.hpp"
#include "common.h"


SCQ::SCQ(size_t new_capacity) : capacity(new_capacity)
{
    tail = 2 * capacity;
    head = 2 * capacity;
    threshold.store(-1);
    
    entries = new std::atomic<SCQ_Element>[capacity];

    for(size_t i = 0; i < capacity; i++)
    {   
        SCQ_Element new_entry = {
            INITIAL_ENTRY_CYCLE,
            INITIAL_ENTRY_ISSAFE,
            INITIAL_ENTRY_INDEX
        };
        entries[i] = new_entry;
    }
}

// Fig 8 Lines 11-22
void SCQ::enqueue(int index)
{
    while(true)
    {
        size_t T = FAA(&tail);
        size_t j = cache_remap(T % capacity, capacity);
        SCQ_Element ent = entries[j].load(std::memory_order_relaxed);

        std::atomic<SCQ_Element> atomic_new_entry;

        load_next: // goto 15 in Fig 8
        SCQ_Element new_entry = { (size_t) T, true, index };
        if(
            (ent.cycle < T) && 
            (ent.index == INITIAL_ENTRY_INDEX) &&
            ((ent.isSafe == true) || (head <= T))
        )
        {
            atomic_new_entry.store({ (size_t) T, true, index });

            if(entries[j].compare_exchange_strong(ent, new_entry))
            {
                goto load_next;
            }

            if(threshold.load() !=  3*(int)capacity - 1)
            {
                threshold.store(3 * capacity - 1);
            }
        }
        return;
    }
}

int SCQ::dequeue()
{
    if(threshold.load() < 0)
        return ERROR_QUEUE_EMPTY;

    while(true)
    {
        int H = FAA(&head);
        int j = cache_remap(H % capacity, capacity);

        load_next: // goto 29 in Fig 8
        SCQ_Element entry = entries[j].load(std::memory_order_relaxed);

        if(entry.cycle == (size_t) H)
        {
            // Cycle can't change, mark as ⊥ ()Fig 8 loc 31
            // Paper uses atomic or which is not part of C++11
            // therefore we simply load it and set the index to ⊥
            SCQ_Element consumed_entry = entries[j];
            consumed_entry.index = INITIAL_ENTRY_INDEX;
            entries[j].store(consumed_entry);

            return entry.index; // Done
        }

        SCQ_Element new_entry = {entry.cycle, false, entry.index};
        if(entry.index == INITIAL_ENTRY_INDEX)
        {
            new_entry = { (size_t) H, entry.isSafe, INITIAL_ENTRY_INDEX};
        }

        if(entry.cycle < (size_t) H)
        {
            if(entries[j].compare_exchange_strong(entry, new_entry))
            {
                goto load_next;
            }
        }

        int T = tail.load();
        if(T <= H + 1)
        {
            // TODO: catchup
            FAA(&threshold) // TODO: FAA für -1
            return ERROR_QUEUE_EMPTY;
        }
        return ERROR_QUEUE_EMPTY;
        // TODO: LOC 44
            
    }
}