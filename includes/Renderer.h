#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

// Custom Headers
#include <config.h>
#include <MathDef.h>

// Standard Headers
#include <iostream>
#include <chrono>
#include <Windows.h>

class CRenderer
{
private:
    wchar_t *output;
    HANDLE outputConsole;
    DWORD outputBytes;
    std::chrono::system_clock::time_point pTime;
    std::chrono::system_clock::time_point cTime;
    float deltaTime;
    int width;
    int height;

public:
    CRenderer()
    {
        width = CWINDOW_WIDTH;
        height = CWINDOW_HEIGHT;
        output = new wchar_t[width * height];
        outputConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(outputConsole);
        outputBytes = 0;
    }

    void start_timer()
    {
        pTime = std::chrono::system_clock::now();
        cTime = std::chrono::system_clock::now();
        deltaTime = 0;
    }

    void set_pixel(int index, char c)
    {
        output[index] = c;
    }

    void new_frame()
    {
        cTime = std::chrono::system_clock::now();
        std::chrono::duration<float> delta = cTime - pTime;
        pTime = cTime;
        deltaTime = delta.count();
    }

    float get_delta()
    {
        return deltaTime;
    }

    void refesh_frame()
    {
        set_pixel(width * height - 1, '\0');
        WriteConsoleOutputCharacterW(outputConsole, output, CWINDOW_WIDTH * CWINDOW_HEIGHT, {0, 0}, &outputBytes);
    }

    CVector get_dimensions()
    {
        return CVector(width, height);
    }

    void draw_screen(CScreen *screen)
    {
        CVector mapDimension = screen->get_dimensions();
        CVector start = screen->get_start();
        for (int y = 0; y < mapDimension.y; y++)
        {
            for (int x = 0; x < mapDimension.x; x++)
            {
                set_pixel((start.y + y) * width + (start.x + x), screen->get_pixel_data(x, y));
            }
        }
    }
};

#endif // CONSOLE_RENDERER_H
