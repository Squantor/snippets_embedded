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
