/*  BigGen.c:
*       Contains functions that generates a big number!
*/

#include "BigNum.h"

//  init():
//      Initialize the big number.
void init(big* a, int len) {
    a->len   = len;
    a->digit = (uint64_t*) malloc(sizeof(uint64_t) * (len+2));
    memset(a->digit, 0, (len+2) * sizeof(uint64_t));
}

//  randbig():
//      Fills <size> digits of big number with random data.
void randbig(big* a, int size) {
    lrlp(i, 1, size)
        a->digit[i] = rand() & LOMSK;
}

//  cleanCarry():
//      Cleaning the carry digit of a big number.
#define cleanCarry(a) (a)->digit[LEN+1] = 0