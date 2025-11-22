#include <iostream>
#include "pixx.h"
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define sleep(x) Sleep((x)*1000)
#else
#include <unistd.h>
#endif
using namespace std;

int getKey() 
{
#ifdef _WIN32
    int c=_getch();
    if(c==0||c==224)
    {
        int n=_getch();
        if(n==72)return 1001;//Up
        if(n==80)return 1002;//Down
        if(n==77)return 1003;//Right
        if(n==75)return 1004;//Left
        return 0;
    }
    if(c==8)return 127; //Backspace
    if(c==13)return '\n'; //Enter
    return c;
#else
    int c=getchar();
    if(c==27) 
    {    
        //ESC
        int n1=getchar();
        if(n1=='[') {
            int n2=getchar();
            if(n2=='A')return 1001;//Up
            if(n2=='B')return 1002;//Down
            if(n2=='C')return 1003;//Right
            if(n2=='D')return 1004;//Left 
        }
        return 27;
    }
    return c;
#endif
}
int main() 
{
    enableRawMode();
    const char* menu[] = 
    {
        "💗 New Pink Screen",
        "💞 Display Princess Page",
        "🌸 Exit"
    };
    int menuSize=3;
    int selected=0;
    clearScreen();
    drawMenu(menu, menuSize, selected);
    bool running=1;
    while(running) 
    {
        int key=getKey();
        if(key==1001||key==1004)  
            selected=(selected-1+menuSize)%menuSize;
        else if(key==1002||key==1003)
            selected=(selected+1)%menuSize;
        else if(key=='\n') 
        {//ENTER
            clearScreen();
            int actionKey=0;
            switch(selected)
            {
                case 0:
                    printCenter("✨ Hello, Princess! ✨", "pink_bright");
                    actionKey=waitAndGetKey(); 
                    break;
                case 1:
                    printCenter("💗 You look good today 💗", "pink_light");
                    actionKey=waitAndGetKey();
                    break;
                case 2:
                    printCenter("🌸 Bye Bye Princess 🌸", "pink_bright");
                    sleep(1);
                    running=0;
                    break;
            }
            if(actionKey==27)//ESC->Exit
                running=0;
            if(running) 
            {
                clearScreen();
                drawMenu(menu, menuSize, selected);
            }
        }
        else if(key==127) 
        {
            clearScreen();
            drawMenu(menu, menuSize, selected);
        }
        else if(key==27) 
            running=0;
        if(running)
            drawMenu(menu, menuSize, selected);
    }
    disableRawMode();
    return 0;
}