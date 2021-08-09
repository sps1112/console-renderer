#ifndef RENDERER_SCREEN_H
#define RENDERER_SCREEN_H

// Custom Headers
#include <Utils.h>
#include <config.h>

// Custom Headers
#include <MathDef.h>

// Renderer Screen Class
class Screen
{
private:
    char *screenPixels; // Pixel Data Stored in the Screen

    // Gets the Index of the Pixel from x,y coordinate
    int get_index(int x, int y)
    {
        return ((y * width) + x);
    }

    // Initializes the Pixels
    void initialize_pixels()
    {
        screenPixels = new char[width * height];
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                {
                    screenPixels[get_index(x, y)] = BORDER_TEXT;
                }
                else
                {
                    screenPixels[get_index(x, y)] = ' ';
                }
            }
        }
    }

public:
    int width;  // Width of the Screen in Pixels
    int height; // Height of the Screen in Pixels

    // Default Screen Constructor
    Screen(int width_, int height_)
    {
        width = width_;
        height = height_;
        initialize_pixels();
    }

    // Prints the Complete Screen
    void print_screen()
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                std::string s(1, screenPixels[get_index(x, y)]);
                print_message(s.c_str());
            }
            log_message("");
        }
    }

    // Clears a line and moves the Cursor to prev line
    void clear_line()
    {
        printf("\33[2K\r\033[A");
    }

    // Clears the complete screen
    void clear_screen()
    {
        for (int y = 0; y < height; y++)
        {
            clear_line();
        }
        printf("\33[2K\r");
    }

    // Sets the Pixel at (x, y) to a character
    void set_pixel(int x, int y, char c)
    {
        screenPixels[get_index(x, y)] = c;
    }

    // Moves the position of a pixel by a direction
    void move_pixel(Position *p, int dir)
    {
        char c = screenPixels[get_index(p->x, p->y)];
        set_pixel(p->x, p->y, ' ');
        switch (dir)
        {
        case 1:
            p->y -= 1;
            break;
        case 2:
            p->x += 1;
            break;
        case 3:
            p->y += 1;
            break;
        case 4:
            p->x -= 1;
            break;
        default:
            break;
        }
        p->x = clamp(p->x, 1, width - 2);
        p->y = clamp(p->y, 1, height - 2);
        set_pixel(p->x, p->y, c);
    }
};

#endif // RENDERER_SCREEN_H
