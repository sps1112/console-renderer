// Custom Headers
#include <Utils.h>
#include <TextRenderer.h>
#include <config.h>
#include <Screen.h>
#include <MathDef.h>

// Standard Headers
#include <iostream>

void get_dir(Screen *screen, Position *p)
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
    int d;
    std::cin >> d;
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    screen->clear_line();
    int dir;
    switch (ch)
    {
    case 'W':
    case 'w':
        dir = 1;
        break;
    case 'D':
    case 'd':
        dir = 2;
        break;
    case 'S':
    case 's':
        dir = 3;
        break;
    case 'A':
    case 'a':
        dir = 4;
        break;
    default:
        dir = 0;
        break;
    }
    screen->move_pixel(p, dir, d);
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
            get_dir(&screen, &p);
        }
        screen.clear_screen();
    }
    log_completion("Finish!");
}
