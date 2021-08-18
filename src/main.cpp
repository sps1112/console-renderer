// Custom Headers
#include <MathDef.h>
#include <Screen.h>
#include <Renderer.h>

// Standard Headers
#include <iostream>

CVector player(15, 8);            // Player Position
float playerSpeed = CURSOR_SPEED; // Player Move Speed

// Checks if the Map is not colliding with Map Border
void check_player(CScreen *map, CVector *displacement)
{
    if (map->index_valid(player.x, player.y))
    {
        if (!map->is_free_pixel(player.x, player.y))
        {
            player.x -= displacement->x;
            player.y -= displacement->y;
            player.x += displacement->x;
            if (!map->is_free_pixel(player.x, player.y))
            {
                player.x -= displacement->x;
            }
            player.y += displacement->y;
            if (!map->is_free_pixel(player.x, player.y))
            {
                player.y -= displacement->y;
            }
        }
    }
}

int main()
{
    // Load Data
    CRenderer renderer;
    CVector mapStart(10, 5);
    CScreen map(mapStart);
    CScreen newMap(10, 8, BORDER_CTEXT, 30, 20);
    CScreen *rendererMap = renderer.get_screen();

    for (int i = 0; i < 4; i++)
    {
        newMap.set_pixel(9, 2 + i, EMPTY_CTEXT);
    }
    for (int i = 0; i < 8; i++)
    {
        map.set_pixel(0, 10 + i, EMPTY_CTEXT);
    }

    // Start Game Loop
    renderer.start_timer();
    while (1)
    {
        // Load New Frame
        renderer.new_frame();

        // Process Data
        CVector displacement;
        displacement.x = renderer.get_axis(0) * playerSpeed;
        displacement.y = renderer.get_axis(1) * playerSpeed;
        player.move(displacement);
        check_player(rendererMap, &displacement);
        check_player(&map, &displacement);
        check_player(&newMap, &displacement);

        // Display Objects
        renderer.draw_screen();
        renderer.draw_screen(&map);
        renderer.draw_screen(&newMap);
        renderer.set_pixel(player.x, player.y, CURSOR_CTEXT);

        // End of Frame
        renderer.refresh_frame();
    }
    return 0;
}
