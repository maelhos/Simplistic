#include "IDT.h"


void InitializeIDT(){
    for (uint64_t t = 0; t < 256; t++)
    {
        _idt[t].zero = 0;
        _idt[t].offset_low =  (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
        _idt[t].offset_mid =  (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
        _idt[t].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);

        _idt[t].ist = 0;
        _idt[t].selector = 0x08;
        _idt[t].types_attr = 0x8e;

    }
    RemapPic();

    outb(PIC1_DATA, 0xfd);
    outb(PIC2_DATA, 0xff);

    LoadIDT();
    //loadKbSettings();
}

extern "C" void isr1_handler(){
    uint8_t scanCode = inb(0x60);
	
	KeyboardHandler(scanCode);
	
    outb(PIC1_COMMAND, PIC_INT_END);
    outb(PIC2_COMMAND, PIC_INT_END);
}