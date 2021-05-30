#include <iostream>
#include <assert.h>

#include "common.h"
#include "SC_Queue.hpp"

using namespace std;

int test_RingBuffer()
{
    cout << "Testing RingBuffer class..." << endl;

    {
        RingBuffer<int> rb(10);
        int a = -2;
        rb.push(a);
        int retVal = rb.pop();
        assert(a == retVal && "Values do not match!");
    }


    {
        RingBuffer<int> rb(10);
        assert(rb.size() == 0);
        int a = -2;
        rb.push(a);
        assert(rb.size() == 1);
        rb.clear();
        assert(rb.size() == 0);
    }



    cout << "Done!" << endl;
    return SUCESS;
}



int test_FAA()
{
    cout << "Testing atomic_fetch_add..." << endl;
    int N = 8;
    int retVal;
    std::atomic<int> cnt(N);

    // Test simple integer increment
    cnt = 0;
    retVal = FAA(&cnt);
    assert(cnt == 1);
    assert(retVal == 0);


    // Test multiple increments
    cnt = 0;
    for(int i = 0; i < 1000; i++)
    {
        retVal = FAA(&cnt);
        assert(cnt == i+1);
        assert(retVal == i);
    }
    


    return SUCESS;
}

int main()
{
    test_RingBuffer();
    test_FAA();
    return 0;
}