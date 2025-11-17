#ifndef PIX_H
#define PIX_H

#include <string>
#include <utility>

void clearScreen();
void setColor(const std::string& colorName);
void gotoXY(int x, int y);
std::pair<int,int> getTerminalSize();
void printCenter(const std::string& text, const std::string& color="white");
void waitForEnter();

#endif
