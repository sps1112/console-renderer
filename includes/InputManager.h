#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

// Standard Headers
#include <iostream>
#include <Windows.h>

// Checks if the Key is being Held
bool get_key_held(char key)
{
    return (GetAsyncKeyState((unsigned short)key) & 0x8000);
}

#endif
