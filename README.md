snippets_embedded
=================

Small snippets that are portable and useful for any embedded systems. Every higher level datastructure contains usually three versions:
* Compact: optimized for low memory consumption, comprises of functions that manipulate one single state struct
* Macro: macro instantiation, quite fast but still generates function code
* Inline: The fastest, usually restricted to one module scope (single file), useful for interrupt routines and such

There are a bunch of datastructures implemented and planned.
* Queue: General purpose queue data structure (WIP)
* Maxheap: Maximum first heap (TODO)
* Minheap: Minimum first heap (TODO)
* Results: Nothing more then a program wide enum that defines the various returnable results like no Error, Out of memory, controller on fire and more. Most of the datastructures or modules define their own Results enum. This datastruct defines the most common ones. (DONE)
* Debug: Debug printouts with various debug levels and module definitions (TODO)

These datastructures are often used in all kinds of facilities that are "snippified" and placed here for use in all kinds of embedded systems.
* Queueing of events, either with or without arguments (WIP)
* Software bus, multiple event generators and listeners (TODO)
* Timer queue, advanced queue that allows single shot or repetative events (TODO)

As you can see in the many empty dirs, there are still a lot that needs to be done. 

Planned
=======
There are still a bunch of things to do.
* Complete the queue variants, by first finishing the compact and then translating it to an inline variant.
* Make files for all three variants with main.c
* Maybe defining CUnit tests for all variants
