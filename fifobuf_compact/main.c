/*
The MIT License (MIT)

Copyright (c) 2015 Anton Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include <stdio.h>
#include <stdlib.h>

#include "results.h"
#include "queue_compact.h"

#define QUEUESIZE   16

struct
{
    uint32_t    dataSize;
    uint32_t    head;
    uint32_t    tail;
    void *      data[QUEUESIZE];
} queueTest;

int dataqueue[QUEUESIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

int main()
{
    int i = 0;
    //int *queuedata;
    void * dataout;
    //void * dummyqueuezero = &dataqueue[1];
    //void * dummyqueueone = &dataqueue[1];
    queueInit(&queueTest, QUEUESIZE-1);
    while( queueEnqueue(&queueTest, &dataqueue[i]) == noError)
    {
        i++;
    }

    while( queueDequeue(&queueTest, &dataout) == noError)
    {
        //queuedata = dataout;
        //blaat = *(int *) dataout;
        printf("dequeued element %d\n", *((int *) dataout));
    }

    return 0;
}
