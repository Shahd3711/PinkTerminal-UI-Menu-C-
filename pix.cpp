#include "pixx.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#endif
using namespace std;

#ifdef _WIN32
HANDLE hConsole;
DWORD orig_mode;
void enableRawMode() {
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hConsole, &orig_mode);
    DWORD mode=orig_mode|0x0004; //ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hConsole, mode);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hConsole, &cci);
    cci.bVisible=0;
    SetConsoleCursorInfo(hConsole, &cci);
}
void disableRawMode() {
    SetConsoleMode(hConsole, orig_mode);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hConsole, &cci);
    cci.bVisible=1;
    SetConsoleCursorInfo(hConsole, &cci);
}
pair<int,int>getTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return { csbi.srWindow.Right-csbi.srWindow.Left+1, csbi.srWindow.Bottom-csbi.srWindow.Top+1 };
}
void flushInput(){
    while(_kbhit())_getch();
}
#else
struct termios orig_termios;
void enableRawMode() 
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    cout<<"\033[?25l"; //Hide Cursor
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void disableRawMode() 
{
    cout<<"\033[?25h"; //Show Cursor
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
pair<int,int>getTerminalSize() 
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return { w.ws_col, w.ws_row };
}
void flushInput() 
{
    tcflush(STDIN_FILENO, TCIFLUSH);
}
#endif

void clearScreen() 
{
    cout<<"\033[2J\033[1;1H";
}
void setColor(const string& colorName)
{
    if(colorName=="pink_bright")cout<<"\033[95m";
    else if(colorName=="pink_light")cout<<"\033[35m";
    else if (colorName == "white")cout<<"\033[97m";
}
void gotoXY(int x, int y) 
{
    cout<<"\033["<<y<<";"<<x<<"H";
}
void printCenter(const string& text, const string& color) 
{
    auto [cols, rows]=getTerminalSize();
    int x=cols/2-text.size()/2;
    int y=rows/2;
    gotoXY(x, y);
    setColor(color);
    cout<<text;
    setColor("white");
}
int waitAndGetKey() 
{
    auto [cols, rows] = getTerminalSize();
    string msg = "Press [DELETE] to Back, [ESC] to Exit";
    gotoXY(cols/2 - msg.size()/2, rows/2 + 2);
    cout<<"\033[90m"<<msg<<"\033[0m"<<flush;
    int c=0;
    bool waiting=1;
    while(waiting)
    {
        #ifdef _WIN32
        c=_getch();
        if(c==8)c=127;
        if(c==13)c='\n';
        #else
        c=getchar();
        #endif
        if(c==127||c==27||c=='\n')
            waiting=0; 
    }
    return c;
}
void drawMenu(const char* menu[], int menuSize, int selected) {
    auto [cols, rows] = getTerminalSize();
    int startY = rows/2 - menuSize/2;
    for (int i = 0; i < menuSize; i++) {
        gotoXY(cols/2 - 10, startY+i);
        if (i == selected) setColor("pink_bright");
        else setColor("pink_light");
        cout << (i == selected ? "> " : "  ") << menu[i];
    }
    setColor("white");
    cout << flush;
}
