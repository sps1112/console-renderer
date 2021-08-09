#ifndef MATH_DEF_H
#define MATH_DEF_H

// Clamps the Value between a Min and Max value
int clamp(int a, int min, int max)
{
    return ((a > max) ? (max) : ((a < min) ? min : a));
}

// 2D Position Struct i.e. (x, y)
struct Position
{
    int x; // X coordinate
    int y; // Y coordinate

    // Default Constructor
    Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    // Moves the Position by (dx, dy)
    void move(int dx = 0, int dy = 0)
    {
        x += dx;
        y += dy;
    }
};

#endif // MATH_DEF_H
