#pragma once

#include <stdint.h>
#include <stddef.h>
#include "print.h"
#include "string.h"
#include "EnvConst.h"
#include "KBScanCode.h"

bool shift = false;
bool shiftHold = false;
uint8_t LastScancode;

void StandardKeyboardHandler(uint8_t scanCode);
void KeyboardHandler0xE0(uint8_t scanCode);
void KeyboardHandler(uint8_t scanCode);
//void SetKeyBoard(uint8_t set);
//void loadKbSettings();



