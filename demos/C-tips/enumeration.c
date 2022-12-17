#include <stdio.h>


//how to use enumeration in C

enum directions{E = 1, W = -1, S = 4, SW = 3, SE = 5};

int main() {
    int board[9] = {0,1,2,3,4,5,6,7,8};

    int curindex = 4;

    printf("SE from index %d is index %d\n", curindex, curindex+SE);


}
