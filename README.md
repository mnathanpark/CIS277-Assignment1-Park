# CIS-277 Assignment 1: Network Packet Buffer Pool

## Student
Nathan Park

## Description
This program is meant to showcase the stack data structure. It displays how the stack can be used, and its limitations.

## Stack Implementation
Vectors
I chose vectors both because I am familiar with it and because its dynamic nature lends itself to Stacks.

## How to Compile
clang++ main.cpp MemoryPool.cpp -o main

## How to Run
After compiling, run ./main if on a unix style operating system or .\main.exe if on Windows.

## Analysis Questions
#Why is a Stack appropriate for managing the free blocks in this memory pool?
A Stack is ideal because pool allocation and deallocation require no specific ordering of blocks. Any available block can serve an incoming request. 

#What happens when the free-block Stack becomes empty?
When the Stack becomes empty, that means all the blocks were allocated already and there is none left on the stack. Any attempt to allocate again will result in a pointer to the null pointer.

Why must a released block be returned to the Stack?
Returning the block to the Stack means that that memory can be reused at a later time without it being destroyed or recreated. 

What problem could occur if the same block were deallocated twice?
The memory address for one block now occupies two spaces in the stack. That means that manipulating one block simultaneously manipulates another block, which is unintended behavior.

What is the Big-O time complexity of allocate()? Explain why.
It is O(1). allocate() just pops the last index currently occupied. There is no need to iterate through the entire vector.

What is the Big-O time complexity of deallocate()? Explain why.
It is O(1). deallocate() just pushes a block onto the stack, appending it to the vector. There is no need to iterate through the entire vector.

## AI Use
Gemini was used to explain the usage of size_t, ptrdiff_t and to help implement the getValidBlockIndex function in MemoryPool.cpp.