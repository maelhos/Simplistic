#pragma once
#include <stdint.h>
#include <stddef.h>

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8868 0x01

#define PIC_INT_END 0x20

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void RemapPic();
