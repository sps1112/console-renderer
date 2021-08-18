#ifndef MATH_DEF_H
#define MATH_DEF_H

// Clamps the Value between a Min and Max value
int clamp(int a, int min, int max)
{
    return ((a > max) ? (max) : ((a < min) ? min : a));
}

// 2D Position Struct i.e. (x, y)
struct CVector
{
    float x; // X coordinate
    float y; // Y coordinate

    // Default Constructor
    CVector(float x_ = 0, float y_ = 0) : x(x_), y(y_) {}

    // Moves the Vector by (dx, dy)
    void move(float dx = 0, float dy = 0)
    {
        x += dx;
        y += dy;
    }

    // Moves the Vector by CVector(x,y)
    void move(CVector vec)
    {
        x += vec.x;
        y += vec.y;
    }
};

#endif // MATH_DEF_H
