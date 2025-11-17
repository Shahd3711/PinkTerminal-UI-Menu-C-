#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "pix.h"

using namespace std;

int readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return -1;

    if (c == '\033') {
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return 27;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return 27;

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return 1001;
                case 'B': return 1002;
            }
        }
        return 27;
    }
    return c;
}

struct termios orig_termios;
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void drawMenu(const vector<string>& menu, int selected) {
    auto [cols, rows] = getTerminalSize();
    int startY = rows / 2 - menu.size();

    for (int i = 0; i < (int)menu.size(); i++) {
        gotoXY(cols/2 - 10, startY + i);
        if (i == selected) setColor("pink_bright");
        else setColor("pink_light");
        cout << (i == selected ? "> " : "  ") << menu[i];
        setColor("white");
    }
}

int main() {
    enableRawMode();

    vector<string> menu = {
        "💗New Pink Screen",
        "💞Display Princess Page",
        "🌸 Exit"
    };
    int selected = 0;

    clearScreen();
    drawMenu(menu, selected);

    while (true) {
        int key = readKey();

        if (key == 1001) {
            selected = (selected - 1 + menu.size()) % menu.size();
        } else if (key == 1002) {
            selected = (selected + 1) % menu.size();
        } else if (key == '\n' || key == 13) {
            clearScreen();
            switch (selected) {
                case 0:
                    printCenter("✨ Hello, Princess! ✨", "pink_bright");
                    waitForEnter();
                    break;
                case 1:
                    printCenter("💗 You look good today 💗", "pink_light");
                    waitForEnter();
                    break;
                case 2:
                    printCenter("🌸 Bye Bye Princess, We'll miss you! 🌸", "pink_bright");
                    disableRawMode();
                    return 0;
            }
            clearScreen();
            drawMenu(menu, selected);
        } else if (key == 'x' || key == 'X') {
            clearScreen();
            printCenter("🌸 Exiting... Bye Bye! 🌸", "pink_bright");
            disableRawMode();
            return 0;
        }

        drawMenu(menu, selected);
    }

    disableRawMode();
    return 0;
}



//cd /Users/shahd37/Documents/codeblocks/
//g++ -Wall -Wextra -std=c++17 main2.cpp pix.cpp -o main2
//./main2