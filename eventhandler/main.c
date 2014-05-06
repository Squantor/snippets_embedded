#include <stdio.h>
#include <stdlib.h>

#include "event.h"

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

    eventInit();
    eventAdd(test1);
    eventAdd(test1);
    eventAdd(test2);
    eventAdd(test3);
    eventAdd(test2);
    eventAdd(test1);
    while(1)
    {
        event newEvent;
        newEvent = eventGet();
        if(newEvent != NULL)
            newEvent();
        else
            break;
    }

    return 0;
}
