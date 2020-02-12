---
layout: post
title: "Writing Synchronization Problems for OS161"
date: 2014-03-20 01:25
comments: true
categories: [c, systems, operating systems, concurrency, synchronization, teaching]
excerpt_separator: <!-- more -->
---

This semester, I have the privilege of being a teaching fellow
for Harvard's legendary [operating systems class](http://www.eecs.harvard.edu/~margo/cs161/),
and I was tasked with writing the synchronization problems for
this year's synchprobs assignment! The goal of these problems
is to get students to think carefully about the synchronization
primitives and data structures needed to solve highly concurrent
problems, avoiding the usual problems that come with concurrency:
race conditions, deadlock, starvation, etc.

I remember how fun these problems
were last year (forming little fellowships of the ring and piazza posts,
meant to mimic creating barriers and reader-writer locks), and
I wanted to make sure the problems were just as fun this year.
I was tasked specifically to write problems to mimic the
synchronization one would use to implement `waitpid()`/`exit()`
(how would you do it?) and the synchronization needed
between address spaces and the coremap when implementing
a virtual memory system in the third assignment. Given
these specifications, I came up with
**Singing Cows** and **~~Hunger~~ Deletion Games** synchprobs!

<!-- more -->

To keep up with the playful spirit of the problems, I
disguised the waitpid/exit problem as a **Singing Cows Problem**:
a daddy cow must wait until each baby cow finishes
singing "Call Me Maybe" before the daddy cow can congratulate
the baby! The final version of the problem eventually
mimicked `wait()` instead, essentially making the daddy
cow wait until **any** baby cow finishes singing.

I had just watched *Hunger Games: Catching Fire*, and this
was my inspiration for the second problem: **~~Hunger~~ Deletion Games**.
In this problem, Katniss and Peeta each have multiple threads
and are attempting to sever mappings between the districts
and the capitol (for the sake of the problem, assume there
are `NSLOTS` districts). These mappings are represented
by a bijection between
capitol slots and district slots. The catch in this problem,
however, is that Katniss and Peeta are concurrently deleting
from opposite sides (Katniss from the capitol side and Peeta
from the district side), so students must avoid
both race conditions (concurrent deletions of the same slot)
and deadlock (concurrent deletions of the same mapping
from opposite sides). This situation mimics the coremap-address
space situation in which threads handling a page fault
need to access a page table entry and then
a coremap entry, while a cleaner thread simultaenously needs
to access a coremap entry and then the corresponding page
table entry. I remember it took me several weeks last year to fully
understand the synchronization needed for this coremap-address space
situation, and I was curious to see what kinds of solutions
students came up with. How would **you** solve this problem?

To see the source code for the problems and scripts to
check the solutions, see the [github repo](https://github.com/kennyyu/cs161-a1scripts).

The problem statements are shown below. Correct implementations should
avoid big lock solutions, and should not allow race conditions,
deadlocks, and starvation.

## Singing Cows

A cow has many children. Each baby cow puts on a performance by singing
lyrics to "Call Me Maybe." Like a good parent, the daddy cow must
sit through each one of its baby cow's performances until the end, in order
to say "Congratulations Baby N!" where N corresponds to the N-th baby cow.

At any given moment, there is a single parent cow and possibly multiple
baby cows singing. The parent cow is not allowed to congratulate a baby
cow until that baby cow has finished singing. Your solution CANNOT
wait for ALL the cows to finish before starting to congratulate the babies.

Here is an example of correct looking output:

```
...
Baby   1 Cow: Hot night, wind was blowin'
Baby   2 Cow: Ripped jeans, skin was showin'
Baby   4 Cow: Don't ask me, I'll never tell
Baby   5 Cow: And this is crazy
Baby   8 Cow: Hot night, wind was blowin'
Parent   Cow: Congratulations Baby 7!
Baby   1 Cow: And now you're in my way
Baby   2 Cow: And now you're in my way
Baby   4 Cow: Hey, I just met you
Baby   5 Cow: Pennies and dimes for a kiss
Baby   8 Cow: But now you're in my way
Parent   Cow: Congratulations Baby 1!
Baby   2 Cow: Ripped jeans, skin was showin'
Baby   4 Cow: I'd trade my soul for a wish
Baby   8 Cow: Hey, I just met you
Parent   Cow: Congratulations Baby 5!
Baby   2 Cow: Your stare was holdin'
Baby   4 Cow: But now you're in my way
Baby   8 Cow: Don't ask me, I'll never tell
Baby   2 Cow: Your stare was holdin'
Baby   4 Cow: Hot night, wind was blowin'
Baby   8 Cow: But now you're in my way
Baby   2 Cow: Your stare was holdin'
Baby   4 Cow: I'd trade my soul for a wish
Baby   8 Cow: But here's my number
Baby   2 Cow: Ripped jeans, skin was showin'
Baby   4 Cow: But now you're in my way
Baby   8 Cow: But now you're in my way
Parent   Cow: Congratulations Baby 2!
Baby   4 Cow: Your stare was holdin'
Baby   8 Cow: Hey, I just met you
Baby   4 Cow: And this is crazy
Baby   8 Cow: I wasn't looking for this
```

## ~~Hunger~~ Deletion Games

Katniss and Peeta are tired of Hunger Games and want to play a new kind
of game instead, the Deletion Games! They want to sever all ties between
the Capitol and all of its districts (for the sake of this problem, assume
that there are actually `NSLOTS` districts). Katniss is severing ties
from the Capitol side, and Peeta is severing ties from the Districts' side.

There is a 1:1 correspondence between `capitol_slots` and `district_slots`. This
means that each slot in `capitol_slots` has exactly one corresponding entry in
`district_slots`, and each slot in `district_slots` has exactly one corresponding
entry in `capitol_slots`. More formally:

```
For all i in {0, 1, 2, ..., NSLOTS - 1},
if capitol_slot[i].is_mapped == true, then
district_slot[capitol_slot[i].district_index].is_mapped == true AND
district_slot[capitol_slot[i].district_index].capitol_index == i

AND similarly if district_slot[i].is_mapped == true.
```

Katniss and Peeta each will use `NTHREADS` to delete these mappings. Katniss
will delete mappings based on randomly generated capitol indices, and Peeta
will delete mappings based on randomly generated district indices.

For example, suppose Katniss randomly chooses capitol index 4 to delete.
She looks at capital slot 4, sees that the slot is still mapped, and finds
the corresponding district index is 12. Then Katniss will free the mappings
in capitol slot 4 and district slot 12.

Suppose Peeta, on the other hand, randomly chooses district index 12 to
delete. He looks at district slot 12, sees that the slot is still mapped,
and finds the corresponding capitol index is 4. Then Peeta will free the
mappings in district slot 12 and capitol slot 4.

However, without proper synchronization, we may get:

*  race conditions: if multiple threads attempt to delete the same mappings at the same time
*  deadlock: Katniss and Peeta try to delete the (capitol 4, district 12)
   mappings at the same time starting from opposite sides
*  starvation: all the mappings must eventually be deleted

Your solution must satisfy these conditions:

*  Avoid race conditions.
*  Avoid any unsynchronized reads (reads on a shared variable without holding the mutex for that variable).
*  No threads may exit until all the mappings have been deleted.
*  Guarantee no deadlock can occur. Your invariants and comments should
   provide a convincing proof of this.
   HINT: You should insert well-placed `thread_yield()` calls in your code to
   convince yourself of no deadlock.
*  When Katniss and Peeta generate random indices to delete, you may decide
   to IGNORE that index if you wish and move onto the next index. However,
   all mappings must eventually be deleted.
   HINT: Use this to your advantage to introduce some asymmetry to the
   problem.

Here is an example of correct looking output:

```
...
{who: katniss, capitol: 86, district: 16, deleted: 114}
{who: katniss, capitol: 108, district: 97, deleted: 115}
{who: peeta, capitol: 89, district: 13, deleted: 116}
{who: katniss, capitol: 103, district: 49, deleted: 117}
{who: katniss, capitol: 5, district: 91, deleted: 118}
{who: peeta, capitol: 57, district: 44, deleted: 119}
{who: katniss, capitol: 39, district: 81, deleted: 120}
{who: katniss, capitol: 55, district: 96, deleted: 121}
{who: peeta, capitol: 101, district: 64, deleted: 122}
{who: katniss, capitol: 44, district: 58, deleted: 123}
{who: katniss, capitol: 59, district: 78, deleted: 124}
{who: katniss, capitol: 80, district: 85, deleted: 125}
{who: katniss, capitol: 122, district: 88, deleted: 126}
{who: katniss, capitol: 67, district: 114, deleted: 127}
{who: katniss, capitol: 61, district: 17, deleted: 128}
```