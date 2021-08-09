// Custom Headers
#include <Utils.h>
#include <TextRenderer.h>
#include <config.h>
#include <Screen.h>
#include <MathDef.h>

// Standard Headers
#include <iostream>

int get_dir(Screen *screen)
{
    log_message(" ");
    log_message("Choose a Direction to Move:");
    log_message("1. W or w for Up");
    log_message("2. D or d for Right");
    log_message("3. S or s for Down");
    log_message("4. A or a for Left");
    log_message("5. Any other letter for None");
    print_message("Choose: ");
    char ch;
    std::cin >> ch;
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    switch (ch)
    {
    case 'W':
    case 'w':
        return 1;
        break;
    case 'D':
    case 'd':
        return 2;
        break;
    case 'S':
    case 's':
        return 3;
        break;
    case 'A':
    case 'a':
        return 4;
        break;
    default:
        return 0;
        break;
    }
}

int main()
{
    log_completion("Start");
    Screen screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    Position p(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    screen.set_pixel(p.x, p.y, CURSOR_TEXT);
    bool quit = false;
    while (!quit)
    {
        screen.print_screen();
        log_message(" ");
        print_message("Enter 0 to quit or any other to continue: ");
        int n;
        std::cin >> n;
        screen.clear_line();
        screen.clear_line();
        if (n == 0)
        {
            quit = true;
        }
        else
        {
            int dir = get_dir(&screen);
            screen.move_pixel(&p, dir);
        }
        screen.clear_screen();
    }
    log_completion("Finish!");
}
