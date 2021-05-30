#include <iostream>
#include <assert.h>
#include <vector>
#include <string>  
#include "common.h"
#include "SC_Queue.hpp"

using namespace std;
//#define VERBOSE

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
    return SUCCESS;
}

//test if ringbuffer has correct size
int test_RB_size()
{
    cout << "testing size of ringbuffer..." << endl;

    for(size_t n = 5; n < 10; n++)
    {
        #ifdef VERBOSE
        cout << "creating ringbuffer of size n = " << n-1 << endl;
        #endif
        RingBuffer<int> rb(n);
        for(size_t i = 0; i < n-1; i++)
            rb.push(i);

        #ifdef VERBOSE
        cout << "ringbuffer actual size: " << rb.size() << endl;
        #endif

        assert(rb.size() == n-1 && "Values do not match!");
    }

    cout << "Done!" << endl;
    return SUCCESS;
}
// test for writing n+n* values into the buffer of size n, the n* values then have to appear at
// entries 0,1,2,..., n* (assuming n* < n, if n* > n, they have to wrap around again) 
// int test_wraparound()
// {
//     cout << "Testing wraparound of RingBuffer class..." << endl;

//     {
//         int n = 3, nstar = 2;
//         size_t currsize = 0;
//         double val = 0, retVal = 0, checkval = 0;
//         RingBuffer<double> rb(n);
//         vector<double> testdata;
//         string msg;

//         for(int i = 0; i < n+nstar; i++)
//         {
//             val = double(i);//+ i/2.);
//             testdata.push_back(val);
//             // #ifdef VERBOSE
//             // cout << "pushing: " << val << endl;
//             // #endif
//             rb.push(val);            
//         }
        
//         #ifdef VERBOSE            
//         cout << "max size of queue: " << to_string(rb.max_size()) << endl;
//         cout << "current size: " << to_string(rb.size()) << endl;
//         #endif 

//         currsize = rb.max_size();
//         for(size_t i = 0; i < currsize; i++)
//         {
//             checkval = testdata[testdata.size() - currsize + i];
//             retVal = rb.pop();
//             msg = "Expected value: " + to_string(checkval) + ", returned value: " + to_string(retVal);

//             #ifdef VERBOSE            
//             cout << msg << endl;
//             #endif
//             //assert(testdata[n+i] == retVal && "Values do not match!");
//         }       
//     }

//     return SUCCESS;
// }

int test_wraparound()
{
    cout << "Testing wraparound of RingBuffer class..." << endl;

    {
        RingBuffer<double> rb(5);
        vector<int> testdata;
        string msg;
        int retVal = 0;

        for(size_t i = 0; i < rb.max_size(); i++)
        {            
            testdata.push_back(i);
            // #ifdef VERBOSE
            // cout << "pushing: " << val << endl;
            // #endif
            rb.push(i);            
        }
        
        // #ifdef VERBOSE            
        // cout << "max size of queue: " << to_string(rb.max_size()) << endl;
        // cout << "current size: " << to_string(rb.size()) << endl;
        // #endif 

        retVal = rb.pop();
        assert(0 == retVal && "Values do not match!");
        retVal = rb.pop();
        assert(1 == retVal && "Values do not match!");
        retVal = rb.pop();
        assert(2 == retVal && "Values do not match!");
        retVal = rb.pop();
        assert(3 == retVal && "Values do not match!");
        retVal = rb.pop();
        assert(4 == retVal && "Values do not match!");

        rb.push(17);  

        rb.push(18);  

        retVal = rb.pop();
        assert(17 == retVal && "Values do not match!");

        retVal = rb.pop();
        assert(18 == retVal && "Values do not match!");
        
        
        //msg = "Expected value: " + to_string(checkval) + ", returned value: " + to_string(retVal);

        //#ifdef VERBOSE            
        //cout << msg << endl;
        //#endif
        //assert(testdata[n+i] == retVal && "Values do not match!");
        
    }

    cout << "Done!" << endl;
    return SUCCESS;
}

int test_consistency()
{
    cout << "testing consistency of ringbuffer..." << endl;

    {
        RingBuffer<double> rb(5);
        vector<int> testdata;
        string msg;
        int retVal = 0;

        for(int i = 0; i < 5; i++)
        {   
            rb.push(i);          
        }

        for(int i = 0; i < 3; i++)
        {   
            retVal = rb.pop();
            //cout << "i = " << i << ", retVal = " << retVal << endl;
            assert(retVal == i && "Values don´t match!");          
        }

        for(int i = 10; i < 15; i++)
        {   
            rb.push(i);          
        }

        // for(int i = 0; i < 5; i++)
        // {   
        //     retVal = rb.pop();
        //     cout << "s_i = " << i << ", retVal = " << retVal << endl;
        //     //assert(retVal == i && "Values don´t match!");          
        // }
        retVal = rb.pop();
        //cout << retVal << endl;
        assert(retVal == 13 && "Values don´t match!");
        retVal = rb.pop();
        //cout << retVal << endl;
        assert(retVal == 14 && "Values don´t match!");
        retVal = rb.pop();
        //cout << retVal << endl;
        assert(retVal == 10 && "Values don´t match!");
        retVal = rb.pop();
        //cout << retVal << endl;
        assert(retVal == 11 && "Values don´t match!");
        retVal = rb.pop();
        //cout << retVal << endl;
        assert(retVal == 12 && "Values don´t match!");
    }

    cout << "Done!" << endl;
    return SUCCESS;
}

int main()
{
    test_RingBuffer();
    test_wraparound();
    test_RB_size();
    test_consistency();
    return 0;
}