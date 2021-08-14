// Custom Headers
#include <MathDef.h>
#include <Screen.h>
#include <Renderer.h>

// Standard Headers
#include <iostream>

float fPlayerX = 14.7f; // Player Start Position
float fPlayerY = 5.09f;
float fSpeed = 5.0f; // Walking Speed

int main()
{
    CRenderer renderer;
    CVector dimensions = renderer.get_dimensions();
    CScreen map;
    map.set_start(3, 3);
    CVector mapStart = map.get_start();
    renderer.start_timer();
    while (1)
    {
        renderer.new_frame();
        CVector displacement;
        // Handle CCW Rotation
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            displacement.x -= fSpeed * renderer.get_delta();
        }
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            displacement.x += fSpeed * renderer.get_delta();
        }
        fPlayerX += displacement.x;
        if (map.get_pixel_data((int)fPlayerX - mapStart.x, (int)fPlayerY - mapStart.y) == BORDER_CTEXT)
        {
            fPlayerX -= displacement.x;
        }
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            displacement.y -= fSpeed * renderer.get_delta();
        }
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            displacement.y += fSpeed * renderer.get_delta();
        }
        fPlayerY += displacement.y;
        if (map.get_pixel_data((int)fPlayerX - mapStart.x, (int)fPlayerY - mapStart.y) == BORDER_CTEXT)
        {
            fPlayerY -= displacement.y;
        }
        for (int y = 0; y < dimensions.y; y++)
        {
            for (int x = 0; x < dimensions.x; x++)
            {
                renderer.set_pixel(y * dimensions.x + x, ' ');
            }
        }
        // Display Map
        renderer.draw_screen(&map);
        renderer.set_pixel(((int)fPlayerY) * dimensions.x + (int)fPlayerX, 'P');

        renderer.refesh_frame();
    }
    return 0;
}
