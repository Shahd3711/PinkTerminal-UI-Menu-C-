#include "pix.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void setColor(const string& colorName) {
    if (colorName == "pink_bright") cout << "\033[95m"; // Bright pink
    else if (colorName == "pink_light") cout << "\033[35m"; // Light pink
    else if (colorName == "white") cout << "\033[97m"; // White
}

void gotoXY(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

pair<int,int> getTerminalSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return { w.ws_col, w.ws_row };
}

void printCenter(const string& text, const string& color) {
    auto [cols, rows] = getTerminalSize();
    int x = cols / 2 - text.size() / 2;
    int y = rows / 2;

    gotoXY(x, y);
    setColor(color);
    cout << text;
    setColor("white");
}

void waitForEnter() {
    cout << "\n\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
