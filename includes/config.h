#ifndef CONFIG_H
#define CONFIG_H

// -----------------------
// Window Settings
// -----------------------
// 1. Outer Window
#define CWINDOW_WIDTH 120
#define CWINDOW_HEIGHT 40
// 2. A Template Screen Window
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 25
// ------------------------------------------

// -----------------------
// Text Settings
// -----------------------
#define SBORDER_CTEXT 'X'
#define BORDER_CTEXT '#'
#define EMPTY_CTEXT ' '
#define CURSOR_CTEXT 'A'
// ------------------------------------------

// -----------------------
// Input Settings
// -----------------------
#define CURSOR_SPEED 10
// ------------------------------------------

// -----------------------
// System Settings
// -----------------------
#define CHECK_WINDOWS (isatty(fileno(stdin)))
// ------------------------------------------

#endif // CONFIG_H
