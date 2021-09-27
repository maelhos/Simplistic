#pragma once

#include <stdint.h>
#include <stddef.h>
#include "IO.h"
#include "printColors.h"

#define VGA_WIDTH 80
#define VGA_HEIGH 25
#define VGA_MEMORY (uint8_t*)0xb8000

void printClear(uint64_t ClearColor = BACKGROUND_BLACK | FOREGROUND_WHITE);
void SetCursorPosition(uint16_t pos);

uint16_t PosFromCoords(uint8_t x, uint8_t y);

void printStr(const char* str, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
void printChar(char chr, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
void print_welcome();

uint16_t CursorPosition;