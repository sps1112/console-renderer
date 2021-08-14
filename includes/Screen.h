#ifndef RENDERER_SCREEN_H
#define RENDERER_SCREEN_H

// Custom Headers
#include <Utils.h>
#include <config.h>

// Custom Headers
#include <MathDef.h>

struct Pixel
{
    wchar_t data;
};

class CScreen
{
private:
    int width;
    int height;
    CVector startEdge;
    Pixel *pixels;

    // Gets the Index of the Pixel from x,y coordinate
    int get_screen_index(int x, int y)
    {
        return ((y * width) + x);
    }

    int get_window_index()
    {
    }

    // Initializes the Pixels
    void initialize_pixels()
    {
        pixels = new Pixel[width * height];
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                {
                    pixels[get_screen_index(x, y)].data = BORDER_CTEXT;
                }
                else
                {
                    pixels[get_screen_index(x, y)].data = EMPTY_CTEXT;
                }
            }
        }
    }

public:
    CScreen(int width_ = SCREEN_WIDTH, int height_ = SCREEN_HEIGHT)
    {
        width = width_;
        height = height_;

        initialize_pixels();
    }
    void set_start(int startX = 0, int startY = 0)
    {
        startEdge.x = startX;
        startEdge.y = startY;
    }

    char get_pixel_data(int x, int y)
    {
        return pixels[get_screen_index(x, y)].data;
    }

    // Sets the Pixel at (x, y) to a character
    void set_pixel(int x, int y, wchar_t c)
    {
        pixels[get_screen_index(x, y)].data = c;
    }

    CVector get_dimensions()
    {
        return CVector(width, height);
    }

    CVector get_start()
    {
        return startEdge;
    }
};

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
                    screenPixels[get_index(x, y)] = BORDER_CTEXT;
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
    void move_pixel(CVector *p, int dir, int dis = 1)
    {
        char c = screenPixels[get_index(p->x, p->y)];
        set_pixel(p->x, p->y, ' ');
        switch (dir)
        {
        case 1:
            p->y -= dis;
            break;
        case 2:
            p->x += dis;
            break;
        case 3:
            p->y += dis;
            break;
        case 4:
            p->x -= dis;
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
