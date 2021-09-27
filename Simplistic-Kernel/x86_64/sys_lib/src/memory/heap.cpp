#include "heap.h"


MemorySegmentHeader* FirstFreeMemorySegment;

void InitializeHeap(uint64_t heapAdress, uint64_t heapLength) {
    FirstFreeMemorySegment = (MemorySegmentHeader*)heapAdress;
    FirstFreeMemorySegment->MemoryLength = heapLength;
    FirstFreeMemorySegment->NextSegment = 0;
    FirstFreeMemorySegment->PreviousSegment = 0;
    FirstFreeMemorySegment->NextFreeSegment = 0;
    FirstFreeMemorySegment->PreviousFreeSegment = 0;
    FirstFreeMemorySegment->Free = true;
}

void* malloc(uint64_t size) {
    uint64_t remainder = size % 8;
    size -= remainder;
    if (remainder != 0) size += 8;

    MemorySegmentHeader* currentMemorySegment = FirstFreeMemorySegment;

    while (true)
    {
        if (currentMemorySegment->MemoryLength >= size)
        {
            if (currentMemorySegment->MemoryLength > size + sizeof(MemorySegmentHeader)){
                MemorySegmentHeader* newSegmentHeader = (MemorySegmentHeader*)((uint64_t)currentMemorySegment + sizeof(MemorySegmentHeader) + size);
                
                newSegmentHeader->Free = true;
                newSegmentHeader->MemoryLength = ((uint64_t)currentMemorySegment->MemoryLength) - (sizeof(MemorySegmentHeader) + size);
                newSegmentHeader->NextFreeSegment = currentMemorySegment->NextFreeSegment;
                newSegmentHeader->NextSegment = currentMemorySegment->NextSegment;
                newSegmentHeader->PreviousSegment = currentMemorySegment;
                newSegmentHeader->PreviousSegment = currentMemorySegment->PreviousSegment;
                newSegmentHeader->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;

                currentMemorySegment->NextFreeSegment = newSegmentHeader;
                currentMemorySegment->NextSegment = newSegmentHeader;
                currentMemorySegment->MemoryLength = size;
            }
            if (currentMemorySegment == FirstFreeMemorySegment) {
                FirstFreeMemorySegment = currentMemorySegment->NextFreeSegment;
            }        
            currentMemorySegment->Free = false;
            currentMemorySegment->MemoryLength = size;
            if (currentMemorySegment->PreviousFreeSegment != 0) currentMemorySegment->PreviousFreeSegment->NextFreeSegment = currentMemorySegment->NextFreeSegment;
            if (currentMemorySegment->NextFreeSegment != 0) currentMemorySegment->NextFreeSegment->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;
            if (currentMemorySegment->PreviousSegment != 0) currentMemorySegment->PreviousSegment->NextFreeSegment = currentMemorySegment->NextFreeSegment;
            if (currentMemorySegment->NextSegment != 0) currentMemorySegment->NextSegment->PreviousFreeSegment = currentMemorySegment->PreviousFreeSegment;


            return currentMemorySegment += 1;        
        }
        if (currentMemorySegment->NextFreeSegment == 0){
            printStr("ERROR : Attempt of malloc but heap is full");
            return 0; // No memory left
        }
        currentMemorySegment = currentMemorySegment->NextFreeSegment;
    }
    return 0;
}

