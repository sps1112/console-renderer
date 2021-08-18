#ifndef RENDERER_SCREEN_H
#define RENDERER_SCREEN_H

// Custom Headers
#include <config.h>
#include <MathDef.h>

// Pixel Data Struct
struct Pixel
{
    wchar_t data;
    // int col = 15; // Color Code of Pixel Text
};

// Console Screen Class
class CScreen
{
private:
    int width;     // Width of Screen
    int height;    // Height of Screen
    CVector start; // Start point of Screen
    Pixel *pixels; // Pixel Array to store data for all pixels of the Screen
    char border;

    // Gets the Index of the Pixel from (x, y) coordinate
    int get_index(int x, int y)
    {
        return ((y * width) + x);
    }

    // Initializes the Pixels with a Border char
    void initialize_pixels()
    {
        pixels = new Pixel[width * height];
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (x == 0 || x == (width - 1) || y == 0 || y == (height - 1))
                {
                    pixels[get_index(x, y)].data = border;
                }
                else
                {
                    pixels[get_index(x, y)].data = EMPTY_CTEXT;
                }
            }
        }
    }

    // Sets the Start Index of Screen
    void set_start(int startX = 0, int startY = 0)
    {
        start.x = startX;
        start.y = startY;
    }

public:
    // Default Screen Constructor
    CScreen(int width_ = SCREEN_WIDTH, int height_ = SCREEN_HEIGHT, char border_ = BORDER_CTEXT, int startX = 0, int startY = 0)
    {
        width = width_;
        height = height_;
        border = border_;
        initialize_pixels();
        set_start(startX, startY);
    }

    // Position Screen Constructor
    CScreen(CVector position, int width_ = SCREEN_WIDTH, int height_ = SCREEN_HEIGHT, char border_ = BORDER_CTEXT)
    {
        width = width_;
        height = height_;
        border = border_;
        initialize_pixels();
        set_start(position.x, position.y);
    }

    // Gets the Data for a Pixel
    wchar_t get_pixel_data(int x, int y)
    {
        return pixels[get_index(x, y)].data;
    }

    bool index_valid(int xWorld, int yWorld)
    {
        int xRel = xWorld - start.x;
        int yRel = yWorld - start.y;
        if (xRel < 0 || yRel < 0 || xRel >= width || yRel >= height)
        {
            return false;
        }
        return true;
    }

    // Gets the Data for a Pixel using World Coordinates
    wchar_t get_pixel_data_world(int xWorld, int yWorld)
    {
        return pixels[get_index(xWorld - start.x, yWorld - start.y)].data;
    }

    // Sets the Pixel at (x, y) to a character
    void set_pixel(int x, int y, wchar_t c)
    {
        pixels[get_index(x, y)].data = c;
    }

    // Returns the Dimensions of the Screen
    CVector get_dimensions()
    {
        return CVector(width, height);
    }

    // Returns the start position of the Screen
    CVector get_start()
    {
        return start;
    }

    // Checks if the given pixel is valid and is not on Border
    bool is_free_pixel(int xWorld, int yWorld)
    {
        if (index_valid(xWorld, yWorld))
        {
            return !(get_pixel_data_world(xWorld, yWorld) == border);
        }
        return true;
    }
};
#endif // RENDERER_SCREEN_H
