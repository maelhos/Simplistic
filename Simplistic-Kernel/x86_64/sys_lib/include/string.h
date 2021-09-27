#pragma once

#include <stdint.h>
#include <stddef.h>

char* itoa(uint32_t val, uint8_t base = 10);
uint16_t strLen(char* str);