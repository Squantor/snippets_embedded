#include "results.h"
#include "queue_compact.h"


results queueInit(void * queueStruct, uint32_t mask)
{
    queueCompact * currentQueue = (queueCompact *) queueStruct;
    currentQueue->mask = mask;
    currentQueue->head = 0;
    currentQueue->tail = 0;
    return noError;
}

results queueEnqueue(void * queueStruct, void * data)
{
    queueCompact * currentQueue = (queueCompact *) queueStruct;
    uint32_t newHead = (currentQueue->head+1) & currentQueue->mask;
    if(newHead == currentQueue->tail)
        return queueFull;
    currentQueue->data[currentQueue->head] = data;
    currentQueue->head = newHead;
    return noError;
}

results queueDequeue(void * queueStruct, void ** data)
{
    queueCompact * currentQueue = (queueCompact *) queueStruct;
    if(currentQueue->head == currentQueue->tail)
        return queueEmpty;
    *data = currentQueue->data[currentQueue->tail];
    currentQueue->tail = (currentQueue->tail+1) & currentQueue->mask;
    return noError;
}


