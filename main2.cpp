#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "pix.h"
using namespace std;

//1001: Up, 1002: Down, 1003: Right, 1004: Left
int main() 
{
    enableRawMode();
    vector<string>menu= 
    {
        "💗New Pink Screen",
        "💞Display Princess Page",
        "🌸 Exit"
    };
    int selected=0;
    clearScreen();
    drawMenu(menu, selected);
    bool running=1; 
    while(running)
    {
        int key=readKey();
        if(key==1001||key==1004)
            selected=(selected-1+menu.size())%menu.size();
        else if(key==1002||key==1003)
            selected=(selected+1)%menu.size();
        else if (key=='\n')
        {
            //Enter
            clearScreen();
            switch(selected) 
            {
                case 0:
                    printCenter("✨ Hello, Princess! ✨", "pink_bright");
                    waitForRawEnter(); 
                    break;
                case 1:
                    printCenter("💗 You look good today 💗", "pink_light");
                    waitForRawEnter(); 
                    break;
                case 2:
                    printCenter("🌸 Bye Bye Princess, We'll miss you! 🌸", "pink_bright");
                    waitForRawEnter();
                    running=0; 
                    break;
            }
            flushInput();
            if(running)
            {
                clearScreen();
                drawMenu(menu, selected);
            }
        }
        else if(key==27||key==127||key=='x'||key=='X')
        { 
            //Exit: Esc, Backspace/Delete, or 'x'
            clearScreen();
            printCenter("🌸 Exiting... Bye Bye! 🌸", "pink_bright");
            disableRawMode();
            running=0; 
        }
        if(running)
            drawMenu(menu, selected);
    }
    disableRawMode();
    return 0;
}
