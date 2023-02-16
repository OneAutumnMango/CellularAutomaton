#include "lib.h"

#define BOUND 0
#define WIDTH 32

extern void println(unsigned int line, unsigned int word);
void next_line(unsigned int, int );

int main() {

    printstr("starting...");
    // next_line((1 << 4)|(1 << 16), 110);
    next_line(0xaaaaaaaa, 110);
    printstr("ending...");
    return 0;
}

void next_line(unsigned int cur, int rule) { // works for any rule in range [0, 256)
    int i;
    unsigned int state;
    unsigned int next = cur;

    for (unsigned int j = 0; j < WIDTH; j++) { // each line per image

        cur = next;

        println(j, next);

        printstr("\nline: "); // print line number to display
        printint(j);
        

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