#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

// Custom Headers
#include <config.h>
#include <MathDef.h>
#include <Screen.h>
#include <InputManager.h>

// Standard Headers
#include <iostream>
#include <chrono>
#include <Windows.h>

// Console Renderer Class
class CRenderer
{
private:
    int width;                                   // Width of Output
    int height;                                  // Height of Output
    wchar_t *output;                             // w_char array to store output data for each pixel
    HANDLE outputConsole;                        // Output Console Handle
    DWORD outputBytes;                           // Bytes Data for Output
    CScreen *mainScreen;                         // A Default Screen for the Renderer
    std::chrono::system_clock::time_point pTime; // Time of previous Frame
    std::chrono::system_clock::time_point cTime; // Time of current Frame
    float deltaTime;                             // Time difference between frames

    // Gets the Index of (x, y) on the Console
    int get_index(int x, int y)
    {
        return (width * y + x);
    }

public:
    // Default Renderer Constructor
    CRenderer(int width_ = CWINDOW_WIDTH, int height_ = CWINDOW_HEIGHT)
    {
        width = width_;
        height = height_;
        output = new wchar_t[width * height + 1];
        outputConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(outputConsole);
        outputBytes = 0;
        mainScreen = new CScreen(width, height, SBORDER_CTEXT);
    }

    // Sets the Pixel Data for the Output
    void set_pixel(int index, wchar_t c)
    {
        output[index] = c;
    }

    // Sets the Pixel at (x,y) to c
    void set_pixel(int x, int y, wchar_t c)
    {
        output[get_index(x, y)] = c;
    }

    // Initializes the Frame Timer
    void start_timer()
    {
        pTime = std::chrono::system_clock::now();
        cTime = std::chrono::system_clock::now();
        deltaTime = 0;
    }

    // Calculates Delta for New Frame
    void new_frame()
    {
        cTime = std::chrono::system_clock::now();
        std::chrono::duration<float> delta = cTime - pTime;
        pTime = cTime;
        deltaTime = delta.count();
    }

    // Gets the Detla Time
    float get_delta()
    {
        return deltaTime;
    }

    // Writes the Output to Screen
    void refresh_frame()
    {
        set_pixel(width * height, '\0');
        WriteConsoleOutputCharacterW(outputConsole, output, width * height + 1, {0, 0}, &outputBytes);
    }

    // Draws the Givern screen to the output
    void draw_screen(CScreen *screen = NULL)
    {
        if (screen == NULL)
        {
            screen = mainScreen;
        }
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

    // Gets the Input Delta Val for given direction (0 ==> Horizontal & 1 ==> Vertical)
    float get_axis(int ch = 0)
    {
        float val = 0;
        if (ch == 0)
        {
            if (get_key_held('A'))
            {
                val -= get_delta();
            }
            if (get_key_held('D'))
            {
                val += get_delta();
            }
        }
        else if (ch == 1)
        {
            if (get_key_held('W'))
            {
                val -= get_delta();
            }
            if (get_key_held('S'))
            {
                val += get_delta();
            }
        }
        return val;
    }

    // Returns the Renderer's Main Screen
    CScreen *get_screen()
    {
        return mainScreen;
    }
};

#endif // CONSOLE_RENDERER_H
