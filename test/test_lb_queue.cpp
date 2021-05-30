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

int main()
{
    test_RingBuffer();
    return 0;
}