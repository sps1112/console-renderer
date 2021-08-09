// Custom Headers
#include <Utils.h>
#include <TextRenderer.h>

// Standard Headers
#include <iostream>

int main()
{
    log_message("Start!");
    log_text_colored("1. Hello World!", COLOR_YELLOW);
    log_text_colored("2. Hello World!", COLOR_YELLOW_BRIGHT);
    log_text_colored("3. Hello World!", COLOR_YELLOW);
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            set_text_color(COLOR_BLUE);
        }
        else
        {
            set_text_color(COLOR_BLUE_BRIGHT);
        }
        std::cout << " " << i << " ";
    }
    log_message("");
    log_error("TEST ERROR!");
    log_completion("Finish!");
}
