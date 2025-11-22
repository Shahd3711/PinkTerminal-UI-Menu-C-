#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H
#include <string>
#include <utility>
using namespace std;
enum colors{ black=30, red, green, yellow, blue, magenta, cyan, white,
bright_black=90, bright_red, bright_green, bright_yellow,
bright_blue, bright_magenta, bright_cyan, bright_white};
void clearScreen();
void setColor(const string& colorName);
void gotoXY(int x, int y);
pair<int,int> getTerminalSize();
void printCenter(const string& text, const string& color);
int waitAndGetKey(); 
void flushInput();
void enableRawMode();
void disableRawMode();
void drawMenu(const char* menu[], int menuSize, int selected);
#endif
