#include "lib.h"

#define BOUND 0
#define WIDTH 32
#define BUTTON 0xffff3100
#define JOYSTICK 0xffff3200

extern void println(unsigned int line, unsigned int word);
void next_line(unsigned int, int );
void start();

int main() {
    start();
    // next_line((1 << 16), 90);
    next_line(1, 110);
    return 0;
}

void start() {
    unsigned int button_state = 0;
    while (button_state)
    {
        unsigned int button = *(volatile unsigned int *)BUTTON;
        unsigned int joystick = *(volatile unsigned int *)JOYSTICK;

        //Check if the button is toggled
        if(button) {
            
        }

        //Check if the joystick is toggled
        if(joystick) {
            
        }
    }
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