#ifndef PIX_H
#define PIX_H

#include <string>
#include <utility>
#include <vector>
#include <termios.h>

extern struct termios orig_termios;

void clearScreen();
void setColor(const std::string& colorName);
void gotoXY(int x, int y);
std::pair<int,int> getTerminalSize();
void printCenter(const std::string& text, const std::string& color="white");
int readKey();
void waitForRawEnter();
void flushInput();
void enableRawMode();
void disableRawMode();
void drawMenu(const std::vector<std::string>& menu, int selected);

#endif
