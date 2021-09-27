#include "print.h"

void printClear(uint64_t ClearColor)
{
  uint64_t value =0;
  value += ClearColor << 8;
  value += ClearColor << 24;
  value += ClearColor << 40;
  value += ClearColor << 56;
  for (uint64_t* i = (uint64_t*)VGA_MEMORY; i < (uint64_t*)(VGA_MEMORY + 4000); i++){
      *i = value;
  }
}

void SetCursorPosition(uint16_t pos){
  if (pos >= VGA_HEIGH*VGA_WIDTH){
    return SetCursorPosition(0);
  }
    outb(0x3d4,0x0f);
    outb(0x3d5,(uint8_t)(pos & 0xff));
    outb(0x3d4,0x0e);
    outb(0x3d5,(uint8_t)((pos >> 8 ) & 0xff));
    CursorPosition = pos;
}
uint16_t PosFromCoords(uint8_t x, uint8_t y){
    return y * VGA_WIDTH + x;
}

void printStr(const char* str, uint8_t color){
  uint8_t* charPtr = (uint8_t*)str;
  uint16_t index = CursorPosition;
  while(*charPtr != 0)
  {
    switch (*charPtr) {
      case 10:
        index += VGA_WIDTH;
        index -= index % VGA_WIDTH;
        break;
      case 13:
        index -= index % VGA_WIDTH;
        break;
      default:
      *(VGA_MEMORY + index * 2) = *charPtr;
      *(VGA_MEMORY + index * 2 + 1) = color;
      index++;
    }

    charPtr++;
  }
  SetCursorPosition(index);
}

void printChar(char chr, uint8_t color)
{
  if (chr == 0){return;} 
  *(VGA_MEMORY + CursorPosition * 2) = chr;
  *(VGA_MEMORY + CursorPosition * 2 + 1) = color;

  SetCursorPosition(CursorPosition + 1);
}


void print_welcome(){
    printClear();
    char* bible = "The Holly bible for sure\n   hehehe";
    printStr((char*)bible);
}