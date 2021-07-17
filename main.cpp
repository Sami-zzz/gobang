#include "game.h"
#include <conio.h>

int main()
{
    while (1) {
        if (startGame() == 1) {
            int win = game1();
            gameOver1(win);
        }
        else {
            int win = game2();
            gameOver2(win);
        }
    }
    return 0;
}



