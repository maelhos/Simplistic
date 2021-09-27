#include "Keyboard.h"


void StandardKeyboardHandler(uint8_t scanCode) {
	bool b_l1 = (scanCode >= 0x10) && (scanCode <= 0x19); // QWERTZUIOP
	bool b_l2 = (scanCode >= 0x1e) && (scanCode <= 0x26); // ASDFGHJKL
	bool b_l3 = (scanCode >= 0x2c) && (scanCode <= 0x32); // YXCVBNMw

	if (b_l1) {
		switch (shift)
		{
		case true:
			printChar(KBSet2::l1[scanCode - 0x10] - 32);
			break;
		case false:
			printChar(KBSet2::l1[scanCode - 0x10]);
			break;
		}

	}
	else if (b_l2) {
		switch (shift)
		{
		case true:
			printChar(KBSet2::l2[scanCode - 0x1e] - 32);
			break;
		case false:
			printChar(KBSet2::l2[scanCode - 0x1e]);
			break;
		}

	}
	else if (b_l3) {
		switch (shift)
		{
		case true:
			printChar(KBSet2::l3[scanCode - 0x2c] - 32);
			break;
		case false:
			printChar(KBSet2::l3[scanCode - 0x2c]);
			break;
		}

	}
	else {
		switch (scanCode) {
		case 0x8E: //Backspace
			SetCursorPosition(CursorPosition - 1);
			printChar(' ');
			SetCursorPosition(CursorPosition - 1);
			break;
		case 0x2A: //Left Shift
			shift = true;
			break;
		case 0xAA: //Left Shift Released
			shift = false;
			break;
		case 0x36: //Right Shift
			shift = true;
			break;
		case 0x39: //Space
			printChar(' ');
			break;
		case 0xB6: //Right Shift Released
			shift = false;
			break;
		case 0x9C: //Enter
			printStr("\n");
			break;
		default:
		{
			if ((scanCode >= 0x90) && (scanCode <= 0xb2)  || (scanCode == 0xb9) || (scanCode == 0x1C) || (scanCode == 0x0e)){ // ignore letter release and other releases
				return;
			}
			printStr("Unrecognzed (hd)  :");
			printStr(itoa(scanCode,16));
			printStr("\n");
			break;
		}
		}
	}
}

void KeyboardHandler0xE0(uint8_t scanCode) {
	printStr("handler E0  :");
	printStr(itoa(scanCode,16));
	printStr("\n");
	switch (scanCode)
	{
	case 0x50:
		SetCursorPosition(CursorPosition + VGA_WIDTH);
		break;
	case 0x48:
		SetCursorPosition(CursorPosition - VGA_WIDTH);
		break;
	default:
		break;
	}

}
/*
void SetKeyBoard(uint8_t set){
	switch (set)
	{
	case 0: {
		char* ll1[] = &KBSet0::l1;
		ll2* = &KBSet0::l2;
		ll3* = &KBSet0::l3;
		break;
	}
	case 1: {
		ll1* = &KBSet1::l1;
		ll2* = &KBSet1::l2;
		ll3* = &KBSet1::l3;
		break;
	}
	case 2: {
		ll1* = &KBSet2::l1;
		ll2* = &KBSet2::l2;
		ll3* = &KBSet2::l3;
		break;
	}

	default:
	{
		ll1* = &KBSet0::l1;
		ll2* = &KBSet0::l2;
		ll3* = &KBSet0::l3;
		break;
	}
	}
}


void loadKbSettings(){
	SetKeyBoard(KeyboardScanCodeSet);
}


*/
void KeyboardHandler(uint8_t scanCode) {

	switch (LastScancode) {
	case 0xE0:
		KeyboardHandler0xE0(scanCode);
		break;
	default:
		StandardKeyboardHandler(scanCode);
	}

	LastScancode = scanCode;
}