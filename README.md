snippets_embedded
=================

Small snippets that are portable and useful for any embedded systems. Every higher level datastructure contains usually three versions:
* Compact: optimized for low memory consumption, comprises of functions that manipulate one single state struct
* Macro: macro instantiation, quite fast but still generates function code
* Inline: The fastest, usually restricted to one module scope (single file), useful for interrupt routines and such

Datastructures
==============
* fifo_(style): circular buffer implementation. Do note that these are not declared volatile and should be done as such when used in ISR's.
* Results: Nothing more then a program wide enum that defines the various returnable results like no Error, Out of memory, controller on fire and more. I generally define one application wide results.h file and let all function pass this result to the caller.
* fp_math_(style): Fixed point macro maths (WIP)

Facilities
==========
These datastructures are often used in all kinds of facilities that are "snippified" and placed here for use in all kinds of embedded systems.
* eventhandlernoargs: Queueing of events, without arguments (WIP)
* eventhandlerargs: Queueing of events, with arguments (WIP)

Planned
=======
There are still a bunch of things to do.
* A few snippets have unit tests but the idea is that all of them have them. The idea is to use the minunit.h unittest framework to realise this.
