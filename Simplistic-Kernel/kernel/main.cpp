#include "main.h"

extern "C" void _start(){
    SetCursorPosition(PosFromCoords(0, 0));
	InitializeIDT();
    InitializeHeap(0x100000,0x100000);

    void* TestMemoryAdress = malloc(10);
    void* TestMemoryAdress2 = malloc(10);
    printStr(itoa((uint64_t)TestMemoryAdress,16));
    printStr("\n");
    printStr(itoa((uint64_t)TestMemoryAdress2,16));
    for (;;){}
    return;
}

