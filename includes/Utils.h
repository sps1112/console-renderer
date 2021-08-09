#ifndef CR_UTILS_H
#define CR_UTILS_H

// Custom Headers
#include <TextRenderer.h>

// Logs a Message to the Console
void log_message(const char *message)
{
    log_text_colored(message);
}

void log_error(const char *error)
{
    log_text_colored(error, COLOR_RED);
}

void log_completion(const char *message)
{
    log_text_colored(message, COLOR_GREEN);
}

#endif // CR_UTILS_H
