snippets_embedded
=================

Small snippets that are portable and useful for any embedded systems. Every higher level datastructure contains usually three versions:
* Compact: optimized for low memory consumption, comprises of functions that manipulate one single state struct
* Macro: macro instantiation, quite fast but still generates function code
* Inline: The fastest, usually restricted to one module scope (single file), useful for interrupt routines and such

There are a bunch of datastructures implemented and planned, most of the empty directories are WIP.
* Queue: General purpose queue data structure
* Maxheap: Maximum first heap
* Minheap: Minimum first heap

These datastructures are often used in all kinds of facilities that are "snippified" and placed here for use in all kinds of embedded systems.
* Queueing of events, either with or without arguments
* Software bus, multiple event generators and listeners
* Timer queue, advanced queue that allows single shot or repetative events

As you can see in the many empty dirs, there are still a lot that needs to be done. 

Planned
=======
There are still a bunch of things to do.
* Complete the queue variants, by first finishing the compact and then translating it to an inline variant.
* Make files for all three variants with main.c
* Maybe defining CUnit tests for all variants
