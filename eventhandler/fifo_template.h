/*
Copyright (c) 2013 Anton Bilos
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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

