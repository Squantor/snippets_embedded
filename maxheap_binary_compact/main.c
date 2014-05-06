#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "results.h"


typedef struct
{
    uint32_t    priority;
    void *      data;
} maxheap_element;

typedef struct
{
    uint32_t            size;
    maxheap_element     heap[32];
} maxheap_binary_compact;

void maxheapBinaryInit(maxheap_binary_compact * heap)
{
    heap->size = 0;
}



results maxheapBinaryHeapify(maxheap_binary_compact * heap)
{
    // take newest element
}

results maxheapBinaryAdd(maxheap_binary_compact * heap, void * data, uint32_t priority)
{
    // check if add is possible
    if(((heap->size+1) * sizeof(maxheap_element)) > sizeof(heap->heap))
    {
        return heapFull;
    }
    // add element
    uint32_t heappos = heap->size;
    heap->heap[heappos].data = data;
    heap->heap[heappos].priority = priority;
    heap->size++;
    // heapify
    return noError;
}

void maxheapBinaryPrint(maxheap_binary_compact * heap)
{
    int i;
    if(heap->size == 0)
        printf("Heap is empty\n");
    for(i=0; i < heap->size; i++)
    {
        printf("heap elem %d, val %p, priority %"PRIu32"\n", i, heap->heap[i].data, heap->heap[i].priority);
    }
}

int main()
{
    maxheap_binary_compact testHeap;
    maxheapBinaryInit(&testHeap);
    maxheapBinaryAdd(&testHeap, NULL, 10);
    maxheapBinaryAdd(&testHeap, NULL, 12);
    maxheapBinaryAdd(&testHeap, NULL, 15);
    maxheapBinaryAdd(&testHeap, NULL, 22);
    maxheapBinaryAdd(&testHeap, NULL, 29);
    maxheapBinaryPrint(&testHeap);
    return 0;
}
