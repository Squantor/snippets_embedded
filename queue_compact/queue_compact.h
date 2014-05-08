#ifndef QUEUE_COMPACT_H_
#define QUEUE_COMPACT_H_

#include <stdint.h>

typedef struct
{
    uint32_t    mask;
    uint32_t    head;
    uint32_t    tail;
    void *      data[];
} queueCompact;

results queueInit(void * queueStruct, uint32_t mask);

results queueEnqueue(void * queueStruct, void * data);

results queueDequeue(void * queueStruct, void ** data);


#endif // QUEUE_COMPACT_H_
