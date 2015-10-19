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
/*
FIFO queue instantiation macro's used by the primary user of the queue.
Restrictions:
only use direct types that can be copied by assignment.
*/

#ifndef __FIFO_TEMPLATE_H__
#define __FIFO_TEMPLATE_H__

#include <stdint.h>
#include "fifo.h"

#define TEMPLATE_FIFO_VARS(name, type, size)                                    \
                                                                                \
    struct                                                                      \
    {                                                                           \
        uint32_t    head;                                                       \
        uint32_t    tail;                                                       \
        type        name[size];                                                 \
    }fifo##name;                                                                \

#define TEMPLATE_FIFO_PROTO(name, type )                                        \
                                                                                \
static void name##Init(void);                                                   \
static fifoResults name##State(void);                                           \
static fifoResults name##Push(type* p);                                         \
static fifoResults name##Pop(type* p);                                          \
static void name##Flush(void);                                                  \
static void name##PushIsr(type* p);                                             \

#define TEMPLATE_FIFO_FUNCTIONS(name, type, size, mask)                         \
                                                                                \
static void name##Init(void)                                                    \
{                                                                               \
    fifo##name.head = fifo##name.tail = 0;                                      \
}                                                                               \
                                                                                \
static fifoResults name##State(void)                                            \
{                                                                               \
    if(fifo##name.head == fifo##name.tail)                                      \
        return fifoEmpty;                                                       \
    else if(((fifo##name.head+1) & mask) == fifo##name.tail)                    \
        return fifoFull;                                                        \
    else                                                                        \
        return fifoNotEmpty;                                                    \
}                                                                               \
                                                                                \
static fifoResults name##Push(type* p)                                          \
{                                                                               \
    uint32_t newHead = (fifo##name.head+1) & mask;                              \
    if(newHead == fifo##name.tail)                                              \
        return fifoFull;                                                        \
    fifo##name.name[fifo##name.head] = *p;                                      \
    fifo##name.head = newHead;                                                  \
    return fifoNoError;                                                         \
}                                                                               \
                                                                                \
static fifoResults name##Pop(type* p)                                           \
{                                                                               \
    if(fifo##name.head == fifo##name.tail)                                      \
        return fifoEmpty;                                                       \
    *p = fifo##name.name[fifo##name.tail];                                      \
    fifo##name.tail = (fifo##name.tail+1) & mask;                               \
    return fifoNoError;                                                         \
}                                                                               \
                                                                                \
static void name##Flush(void)                                                   \
{                                                                               \
    fifo##name.tail = fifo##name.head;                                          \
}                                                                               \

#endif

