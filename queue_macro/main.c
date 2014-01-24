#include <stdio.h>
#include <stdlib.h>

#include "results.h"
#include "queue_macro.h"

typedef void (*event)(void);

TEMPLATE_QUEUE_PROTO(events, event)
TEMPLATE_QUEUE_VARS(events, event, 8)
TEMPLATE_QUEUE_FUNCTIONS(events, event, 8, 7)

void test1()
{
    printf("test1\n");
}

void test2()
{
    printf("test2\n");
}

void test3()
{
    printf("test3\n");
}

int main()
{
    event tempEvent;
    eventsInit();
    tempEvent = test1;
    eventsEnqueue(&tempEvent);
    tempEvent = test1;
    eventsEnqueue(&tempEvent);
    tempEvent = test3;
    eventsEnqueue(&tempEvent);
    tempEvent = test2;
    eventsEnqueue(&tempEvent);
    tempEvent = test3;
    eventsEnqueue(&tempEvent);
    while(eventsDequeue(&tempEvent) == noError)
        tempEvent();
    while(eventsEnqueue(&tempEvent) == noError)
        ;
    while(eventsDequeue(&tempEvent) == noError)
        tempEvent();
    return 0;
}
