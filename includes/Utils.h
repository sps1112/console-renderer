#ifndef CR_UTILS_H
#define CR_UTILS_H

// Custom Headers
#include <TextRenderer.h>

namespace cren
{
    // Default Error text
    Style errorStyle = Style(Color(COLOR_RED, true));

    // Default Completion text
    Style completionStyle = Style(Color(COLOR_GREEN, true));

    // Prints a Message to the Console
    void print_message(const char *message)
    {
        print_text_colored(message, &defaultStyle);
    }

    // Logs a Message to the Console
    void log_message(const char *message)
    {
        log_text_colored(message, &defaultStyle);
    }

    // Logs an Error Message with a different Color
    void log_error(const char *error)
    {
        log_text_colored(error, &errorStyle);
    }

    // Logs an Completion Message with a different Color
    void log_completion(const char *message)
    {
        log_text_colored(message, &completionStyle);
    }
}

#endif // CR_UTILS_H
