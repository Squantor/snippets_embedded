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
simple event handling queue
*/

#include <stdint.h>
#include <stdlib.h>

#include "event.h"
#include "fifo.h"
#include "fifo_template.h"

/* --- Constants --- */
#define     EVENT_QUEUE_SIZE    64
#define     EVENT_QUEUE_MASK    63

/* --- types --- */

/* --- module variables --- */
TEMPLATE_FIFO_VARS(events, event, EVENT_QUEUE_SIZE)

/* --- private function prototypes --- */
TEMPLATE_FIFO_PROTO(events, event)

/* --- private functions --- */
TEMPLATE_FIFO_FUNCTIONS(events, event, EVENT_QUEUE_SIZE, EVENT_QUEUE_MASK)

/* --- public functions --- */
void eventInit(void)
{
    eventsInit();
}

eventResults eventAdd(event pending)
{
    return eventsPush(&pending);
}

event eventGet(void)
{
    event pending;
    fifoResults result = eventsPop(&pending);
    if(result == fifoNoError)
        return pending;
    else
        return NULL;
}
