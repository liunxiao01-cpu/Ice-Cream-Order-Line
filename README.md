## Ice Cream Order Queue System

## Description
The Ice Cream Order Queue System is a C++ terminal-based program that manages an ice cream shop order line.
Customers join a hand-built **FIFO queue** and are served in the order they arrived. Once an order is served,
it's moved into a separate **sales history**, so staff can look back at everything already sold without
disturbing the live queue.

## Features
* Take a new ice cream order
* Serve the next customer
* Display the live order queue
* View the sales history log
* Search the active queue by flavor
* Sort the active queue by Order ID
* Exit cleanly — memory is freed automatically when the program ends

## How to Compile & Run

```bash
g++ -std=c++17 -Wall -o icecream ice_cream_fixed.cpp
./icecream
```

Requires a C++11-or-later compiler (e.g. `g++`, `clang++`). No external libraries —
only `<iostream>` and `<string>`. The program starts with 7 sample orders (IDs 101–107)
already loaded into the queue, so every menu option can be explored right away.

## Data Structures & Algorithms
* **Hand-Built FIFO Queue (`IceCreamQueue`)** — tracks `front` and `rear` pointers so `enqueue()`/`dequeue()` are both O(1)
* **Hand-Built Linked List (`LinkedList`)** — a separate structure from the queue; archives every served order
* **Order Array** — a snapshot of the active queue, used for searching and sorting
* **Bubble Sort** — hand-written; sorts the array snapshot by Order ID
* **Classes & Pointers** — used throughout for object-oriented programming and manual memory management

> **Note:** search and sort only look at the **active queue**. Once an order is served, it moves to the
> sales history and is no longer searchable or sortable this way — that's by design, not a bug.

## Classes

### IceCream
Stores:
* Order ID
* Flavor
* Quantity

Has a constructor and destructor (private fields, printed confirmation messages on each) — satisfies the
OOP and memory-management requirement.

### QueueNode
Used only inside `IceCreamQueue`. Stores:
* Pointer to an `IceCream` order
* Price
* Pointer to the next node

### IceCreamQueue
The live FIFO order line. Tracks `front` and `rear` pointers for true O(1) `enqueue()`/`dequeue()`.
Its destructor frees any orders still waiting when the program exits.

### ListNode
Used only inside `LinkedList`. Stores:
* Pointer to an archived `IceCream` order
* Final price
* Pointer to the next node

### LinkedList
The permanent sales history — a separate structure from `IceCreamQueue`. Once an order is served,
ownership of it moves here. Its destructor frees every archived order.

## Team Members
* SOTH Sokharn
* Na Sreypich
* Toch Sreynit
* Taing Meng Kim

## Course
**Advanced Algorithm and C++**

## Project
**Week 5 Mini-Project**
