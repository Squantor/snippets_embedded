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
queue instantiation macro's used by the primary user of the queue.
Restrictions:
only use direct types that can be copied by assignment.
*/

#ifndef __QUEUE_TEMPLATE_H__
#define __QUEUE_TEMPLATE_H__

#include <stdint.h>
#include "results.h"

#define TEMPLATE_QUEUE_VARS(name, type, size)                                   \
                                                                                \
    struct                                                                      \
    {                                                                           \
        uint32_t    head;                                                       \
        uint32_t    tail;                                                       \
        type        name[size];                                                 \
    }queue##name;                                                               \

#define TEMPLATE_QUEUE_PROTO(name, type )                                       \
                                                                                \
static void name##Init(void);                                                   \
static results name##State(void);                                               \
static results name##Enqueue(type* p);                                          \
static results name##Dequeue(type* p);                                          \

#define TEMPLATE_QUEUE_FUNCTIONS(name, type, size, mask)                        \
                                                                                \
static void name##Init(void)                                                    \
{                                                                               \
    queue##name.head = queue##name.tail = 0;                                    \
}                                                                               \
                                                                                \
static results name##State(void)                                                \
{                                                                               \
    if(queue##name.head == queue##name.tail)                                    \
        return queueEmpty;                                                      \
    else if(((queue##name.head+1) & mask) == queue##name.tail)                  \
        return queueFull;                                                       \
    else                                                                        \
        return queueNotEmpty;                                                   \
}                                                                               \
                                                                                \
static results name##Enqueue(type* p)                                           \
{                                                                               \
    uint32_t newHead = (queue##name.head+1) & mask;                             \
    if(newHead == queue##name.tail)                                             \
        return queueFull;                                                       \
    queue##name.name[queue##name.head] = *p;                                    \
    queue##name.head = newHead;                                                 \
    return noError;                                                             \
}                                                                               \
                                                                                \
static results name##Dequeue(type* p)                                           \
{                                                                               \
    if(queue##name.head == queue##name.tail)                                    \
        return queueEmpty;                                                      \
    *p = queue##name.name[queue##name.tail];                                    \
    queue##name.tail = (queue##name.tail+1) & mask;                             \
    return noError;                                                             \
}                                                                               \
                                                                                \

#endif

