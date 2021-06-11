#include <iostream>
#include <assert.h>

#include "SCQ.hpp"
#include "common.h"


using namespace std;

int test_scq_init()
{
    cout << "Testing SCQ Constructur" << endl;
    
    { SCQ scq(10); } // smol init

    { 
        SCQ scq((int) 1e7); 
        }  // big init    
    
    return SUCCESS;
}

int test_scq_enqueu()
{
    return SUCCESS;
}



int main()
{
    assert(test_scq_init() == SUCCESS);
}