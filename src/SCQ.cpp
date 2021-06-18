#include "SCQ.hpp"
#include "common.h"


SCQ::SCQ(size_t capacity = 0) : m_capacity(capacity)
{
    tail = 2 * m_capacity;
    head = 2 * m_capacity;
    threshold.store(-1);
    
    entries = new std::atomic<SCQ_Element>[m_capacity];

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
        size_t T = FAA(&tail, 1);
        size_t j = cache_remap(T % m_capacity, m_capacity);
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

            if(threshold.load() !=  3*(int)m_capacity - 1)
            {
                threshold.store(3 * m_capacity - 1);
            }
        }
        return;
    }
}

int SCQ::dequeue()
{
    if(threshold.load() < 0)
    {
        return ERROR_QUEUE_EMPTY;
    }
        
    while(true)
    {
        int H = FAA(&head, 1);
        int j = cache_remap(H % m_capacity, m_capacity);

        load_next: // goto 29 in Fig 8
        SCQ_Element entry = entries[j].load(std::memory_order_relaxed);

        if(entry.cycle == (size_t) H)
        {
            // Cycle can't change, mark as ⊥ (Fig 8 loc 31)
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

        // TODO: rewrite to be more readable
        int T = tail.load();
        if(T <= H + 1)
        {
            catchup(T, H + 1);
            FAA(&threshold, -1);
            return ERROR_QUEUE_EMPTY;
        }

        int t = FAA(&threshold, -1);
        if(t < 0)   // for some reason GCC does not want me to put FAA in here
        {
            return ERROR_QUEUE_EMPTY;
        }       
    }
}


void SCQ::catchup(size_t t, int h)
{
    tail.compare_exchange_strong(t ,(size_t) h);
    while(true)
    {
        h = head.load();
        t = tail.load();
        if((int) t >= h)
        {
            break;
        }
    }
}

// constructor according to Fig. 4
FIFO_Queue::FIFO_Queue(size_t capacity) : m_capacity(capacity)
{ 
    m_data = new std::vector<int>*[capacity];
    m_size = 0;

    // aq initiualized empty
    aq = new SCQ(m_capacity);
    
    // fq initialized full
    fq = new SCQ(m_capacity);
    for(size_t i = 0; i < m_capacity; i++)
    {
        fq->enqueue(i);
    }
}


FIFO_Queue::~FIFO_Queue()
{
    delete[] m_data;
    delete aq;
    delete fq;
}


int FIFO_Queue::enqueue(std::vector<int> * obj)
{
    int index = fq->dequeue();
    if(index == ERROR_QUEUE_EMPTY)
    {
        // no free elements available -> FIFO queue is full
        return ERROR_QUEUE_FULL;
    }


    m_data[index] = obj;
    aq->enqueue(index);
    FAA(&m_size, 1);
    
    return SUCCESS;
}

std::vector<int> * FIFO_Queue::dequeue()
{
    int index = aq->dequeue();
    if(index == ERROR_QUEUE_EMPTY)
    {
        // FIFO Queue is empty
        return nullptr;
    }
    std::vector<int> * ptr = m_data[index];
    fq->enqueue(index);
    FAA(&m_size, -1);

    return ptr;
}