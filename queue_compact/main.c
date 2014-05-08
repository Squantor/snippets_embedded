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
