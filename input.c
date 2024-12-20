#include <stdio.h>
#include <uchar.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <process.h>
#include <conio.h>
#include "input.h"

static void* keylistener(void* arg) {
    int arrowDown = 80;
    int arrowUp = 72;
    while (1) {
        char key = _getch();
        if (key == 'd' || key == 'l') { Input.x = +1; Input.y = 0; }
        if (key == 'a' || key == 'j') { Input.x = -1; Input.y = 0; }

        if (key == 's' || key == 'k') { Input.x = 0; Input.y = +1; }
        if (key == 'w' || key == 'i') { Input.x = 0; Input.y = -1; }
    }
}

void setupKeyboard() {
	int tid = _beginthread(&keylistener, 4096, 0);
}