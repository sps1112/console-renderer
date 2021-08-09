#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

// Standard Headers
#include <iostream>
#include <string>

// Types of Colors for Text
enum TEXT_COLOR
{
    COLOR_WHITE,
    COLOR_RESET,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_RED_BRIGHT,
    COLOR_GREEN_BRIGHT,
    COLOR_BLUE_BRIGHT,
    COLOR_YELLOW_BRIGHT,
};

// Prefix for Text Color ANSI Code
std::string colPrefix = "\u001b[";

// Postfix for Text Color ANSI Code
std::string colPostfix = "m";

// ANSI Code for Bright Colors
std::string brightTextCode = ";1";

// Text Color Data Struct
struct TextColor
{
    TEXT_COLOR col;   // Color of the Text
    std::string code; // ANSI Code for that Color
    bool isBright;    // If the Color is Bright or Not

    // Default Constructor
    TextColor(TEXT_COLOR col_ = COLOR_WHITE, std::string code_ = "37", bool bright = false)
        : col(col_), code(code_), isBright(bright) {}

    // Returns the Complete ANSI Code for the Text Color
    std::string get_code()
    {
        if (isBright)
        {
            return (colPrefix + code + brightTextCode + colPostfix);
        }
        return (colPrefix + code + colPostfix);
    }
};

// Default TextColor templates
TextColor textColors[] = {
    TextColor(COLOR_WHITE, "37"),
    TextColor(COLOR_RESET, "0"),
    TextColor(COLOR_RED, "31"),
    TextColor(COLOR_GREEN, "32"),
    TextColor(COLOR_BLUE, "34"),
    TextColor(COLOR_YELLOW, "33"),
    TextColor(COLOR_RED_BRIGHT, "31", true),
    TextColor(COLOR_GREEN_BRIGHT, "32", true),
    TextColor(COLOR_BLUE_BRIGHT, "34", true),
    TextColor(COLOR_YELLOW_BRIGHT, "33", true)};

// Resets the Text Color
void reset_text_color()
{
    printf(textColors[COLOR_RESET].get_code().c_str());
}

// Sets the Text Color to a certain color
void set_text_color(TEXT_COLOR col = COLOR_WHITE)
{
    reset_text_color();
    printf(textColors[col].get_code().c_str());
}

// Prints a message with a given color
void print_text_colored(const char *message, TEXT_COLOR col = COLOR_WHITE)
{
    set_text_color(col);
    std::cout << message;
    reset_text_color();
}

// Logs a message with a given color
void log_text_colored(const char *message, TEXT_COLOR col = COLOR_WHITE)
{
    print_text_colored(message, col);
    std::cout << std::endl;
}

#endif // TEXT_RENDERER_H
