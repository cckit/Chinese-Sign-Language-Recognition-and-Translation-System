#include <Windows.h>

void performMouseClick(bool isLeft){
	keybd_event(isLeft ? VK_RIGHT : VK_LEFT, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
}