#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

// Custom Headers
#include <config.h>

// Standard Headers
#include <iostream>
#include <string>
#include <stdio.h>
#include <io.h>
#include <Windows.h>

// Prefix for Text Color ANSI Code
std::string colPrefix = "\u001b[";

// ANSI Text Code
std::string textCode = "3";

// ANSI Background Code
std::string backgroundCode = "4";

// Postfix for Text Color ANSI Code
std::string colPostfix = "m";

// ANSI Code for Bright Colors
std::string brightCode = ";1";

// Output Handle Console
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// The Console Renderer Namespace
namespace cren
{
    // Template Colors which can be used by Texts or Background
    enum COLOR_TEMPLATE
    {                 // #Bash /#Console
        COLOR_BLACK,  // #0 /#0
        COLOR_RED,    // #1 /#4
        COLOR_GREEN,  // #2 /#2
        COLOR_YELLOW, // #3 /#6
        COLOR_BLUE,   // #4 /#1
        COLOR_PURPLE, // #5 /#5
        COLOR_AQUA,   // #6 /#3
        COLOR_WHITE,  // #7 /#7
    };

    // Gets Color Code from int ID
    COLOR_TEMPLATE get_color(int id)
    {
        return static_cast<COLOR_TEMPLATE>(id);
    }

    // Converts to Equivalent Windows code
    COLOR_TEMPLATE get_windows_code(COLOR_TEMPLATE col)
    {
        int id = (int)col;
        switch (id)
        {
        case 1:
            return get_color(4);
        case 3:
            return get_color(6);
        case 4:
            return get_color(1);
        case 6:
            return get_color(3);
        default:
            return get_color(id);
        }
    }

    // Console Color Struct
    struct Color
    {
        COLOR_TEMPLATE col; // The Color of Object
        bool bright;        // If the Object Color is Bright Version
        Color(COLOR_TEMPLATE col_ = COLOR_WHITE, bool bright_ = false) : col(col_), bright(bright_) {}
    };

    // Console Object Style Struct
    struct Style
    {
        Color text;       // Color of the Text
        Color background; // Color of the Background
        Style(Color text_ = Color(COLOR_WHITE), Color background_ = Color(COLOR_BLACK))
            : text(text_), background(background_) {}

        // Gets the string code of Background color
        std::string get_bg_code()
        {
            if (background.bright)
            {
                return (colPrefix + backgroundCode + std::to_string(background.col) + brightCode + colPostfix);
            }
            return (colPrefix + backgroundCode + std::to_string(background.col) + colPostfix);
        }

        // Gets the string code of Text color
        std::string get_text_code()
        {
            if (text.bright)
            {
                return (colPrefix + textCode + std::to_string(text.col) + brightCode + colPostfix);
            }
            return (colPrefix + textCode + std::to_string(text.col) + colPostfix);
        }
    };

    // Default white text
    Style defaultStyle;

    // Resets the Text Color
    void reset_color()
    {
        if (CHECK_WINDOWS)
        {
            SetConsoleTextAttribute(hConsole, 15);
        }
        else
        {
            printf((colPrefix + std::to_string(0) + colPostfix).c_str());
        }
    }

    // Sets the Text Color to a certain color
    void set_color(Style *style)
    {
        reset_color();
        if (CHECK_WINDOWS)
        {
            int textID = get_windows_code(style->text.col);
            int bgID = get_windows_code(style->background.col);
            if (style->text.bright)
            {
                textID += 8;
            }
            if (style->background.bright)
            {
                bgID += 8;
            }
            SetConsoleTextAttribute(hConsole, textID + bgID * 16);
        }
        else
        {
            printf(style->get_bg_code().c_str());
            printf(style->get_text_code().c_str());
        }
    }

    // Prints a message with a given color
    void print_text_colored(const char *message, Style *style = &defaultStyle)
    {
        set_color(style);
        std::cout << message;
        reset_color();
    }

    // Logs a message with a given color
    void log_text_colored(const char *message, Style *style = &defaultStyle)
    {
        print_text_colored(message, style);
        std::cout << std::endl;
    }

    // Prints a message with a given color
    void print_text_colored(const char *message, COLOR_TEMPLATE col = COLOR_WHITE, COLOR_TEMPLATE background = COLOR_BLACK)
    {
        Style style = Style(Color(col), Color(background));
        set_color(&style);
        std::cout << message;
        reset_color();
    }

    // Logs a message with a given color
    void log_text_colored(const char *message, COLOR_TEMPLATE col = COLOR_WHITE, COLOR_TEMPLATE background = COLOR_BLACK)
    {
        print_text_colored(message, col, background);
        std::cout << std::endl;
    }
}

#endif // TEXT_RENDERER_H
