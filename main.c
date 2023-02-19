#include "lib.h"

#define BOUND 0
#define WIDTH 32
#define STARTPIX 0xffff8000

extern void println(unsigned int line, unsigned int word);
void next_line(unsigned int, int );
unsigned int start();
void setpixel(int x, int y);

int main() {
    next_line(start(), 110);
    return 0;
}

unsigned int start() {
    int y = 0;
    unsigned int button = (volatile unsigned int)0xffff3100;
    unsigned int joystick = (volatile unsigned int)0xffff3200;
    unsigned int stop = (volatile unsigned int)0xffff3300;
    int word = 0;
    for (;;)
    {
        for (int i = 0; i < 16; i++) {
            if (i == 0) {
                *((volatile int *)(STARTPIX + y*0x4)) ^= 0x80000000; //on
                *((volatile int *)(STARTPIX + y*0x4)) ^= 0x80000000; //off
            }
        }

        if (joystick) {
            switch(joystick) {
            case 0b1111:
                if(y < WIDTH - 1) y+=1;
                break;
            case 0b0001:
                if (y > 0) y-=1;
                break;
            }
        }

        if (button) {
            *((volatile int *)(STARTPIX + y*4)) ^= 0x80000000;
        }

        if (stop) break;
        

        /*
        unsigned int button = *(volatile unsigned int *)BUTTON;
        unsigned int joystick = *(volatile unsigned int *)JOYSTICK;
        for(i = 0; i < WIDTH; i++) {
            for(j = 0; j < 1; j++) {
                //Check if the button is toggled
                if(button) {
                    setpixel(j, i);
                }

                //Check if the joystick is toggled

                if(joystick) {
            
                }
                
            }
        }
        */
    }
}

void setpixel(int x, int y) {
    unsigned int *display = (unsigned int *)0xffff8000;
    display[y] = display[y] | (0x1 << x);
}

void next_line(unsigned int cur, int rule) { // works for any rule in range [0, 256)
    int i;
    unsigned int state;
    unsigned int next = cur;

    for (unsigned int j = 0; j < WIDTH; j++) { // each line per image
        cur = next;


        println(j, next);
        // printstr("\nline: "); // print line number to display
        // printint(j);

        next = 0;
        for (i = 0; i < WIDTH; i++) { // each pixel per line
            // state = 7 & (cur >> (i - 1) | cur << (WIDTH + 1 - i));   /* for looping boundaries - this would replace the entire switch statement */
            switch (i) {
            case 0:
                state = 7 & (cur << 1 | BOUND); // 7 = 0b00000111 -> gets first 3 bits
                break;
            case WIDTH - 1:
                state = 7 & (cur >> (WIDTH - 2) | BOUND << 2);
                break;
            default:
                state = 7 & (cur >> i - 1);
            }

            if (rule & (1 << state)) { // checks value for rule using its binary
                next |= 1 << i;
            }
        }
    }
}
