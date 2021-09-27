#pragma once
#include <stdint.h>
#include <stddef.h>
#include "print.h"
struct MemorySegmentHeader {
    uint64_t MemoryLength;
    MemorySegmentHeader* NextSegment;
    MemorySegmentHeader* PreviousSegment;
    MemorySegmentHeader* NextFreeSegment;
    MemorySegmentHeader* PreviousFreeSegment;
    bool Free;
};

extern void InitializeHeap(uint64_t heapAdress, uint64_t heapLength);

extern void* malloc(uint64_t size);

