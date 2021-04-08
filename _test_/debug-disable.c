#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define measureTime( tstFunc ) do {\
    struct timespec _b_;\
    struct timespec _c_;\
    clock_gettime(CLOCK_MONOTONIC, &_b_);\
    tstFunc\
    clock_gettime(CLOCK_MONOTONIC, &_c_);\
    printf("[i] Time elapsed: %ldns\n", _c_.tv_sec * 1000000000 + _c_.tv_nsec - _b_.tv_sec * 1000000000 - _b_.tv_nsec); \
} while(0)    

// Shorthand defition for loop commands
#define loop(_i_, _n_)       for (int _i_ = 0;   _i_ <  (int)_n_; ++_i_)
#define lrlp(_i_, _l_, _r_)  for (int _i_ = _l_; _i_ <= (int)_r_; ++_i_)
#define rllp(_i_, _r_, _l_)  for (int _i_ = _r_; _i_ >= (int)_l_; --_i_)

/*
    Variable defzeroons
*/
#define LEN    1024                  // Length of the array in big number.
// Shift values that are commonly used
#define AC_SHIFT 32                 // To get addition carry bit
#define SC_SHIFT 63                 // To get subtraction carry bit
// Mask values that are commonly used
#define LOMSK  0x00000000ffffffff
#define HIMSK  0xffffffff00000000
#define BASE   0x0000000100000000

/*
    Struct
*/
typedef struct _big_ {
    int       len;
    uint64_t *digit;
} big;

void pb(uint64_t ui) {
    // rllp(i, 63, 32)
    //     printf(ui >> i & 0x1 ? "1":"0");
    // printf("|");
    rllp(i, 31, 0)
        printf(ui >> i & 0x1 ? "1":"0");
}

void pi(uint64_t ui) {
    printf("%lu", ui);
}

void print(big a) {
    char buf[100000]; memset(buf, 0, sizeof(buf));
    strcpy(buf, "python3 -c \"print(");
    lrlp(i, 1, a.len) {
        char term[50]; memset(term, 0, sizeof(term));
        sprintf(term, "%lu*2**%d+", a.digit[i], (i-1)*32);        
        strcat(buf, term);
    }
    strcat(buf, "0, end='')\"");
    int result = system(buf);
}

void printBinary(big a) {
    rllp(i, a.len+1, 1)
        pb(a.digit[i]),
        printf(" ");
}

//  init():
//      Initialize the big number.
void init(big* a, int len) {
    a->len   = len;
    a->digit = (uint64_t*) calloc(len+2, sizeof(uint64_t));
}

//  randbig():
//      Fills <size> digits of big number with random data.
void randbig(big* a, int size) {
    lrlp(i, 1, size)
        a->digit[i] = rand() & LOMSK;
}

#define carry(a) a.digit[a.len+1]

//  add():
//      Add 2 big numbers.
big add(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len+1) {
        c.digit[i]    = a.digit[i] + b.digit[i] + (c.digit[i-1] >> AC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    c.digit[a.len+1] &= 0x1;
    return c;
}

//  sub():
//      Subtract 2 big numbers.
big sub(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len+1) {
        c.digit[i]    = a.digit[i] - b.digit[i] - (c.digit[i-1] >> SC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    c.digit[a.len+1] &= 0x1;
    return c;
}

//  neg():
//      Convert x to -x.
void neg(big* a) {
    a->digit[0] = BASE;
    lrlp(i, 1, a->len+1) {
        a->digit[i]    = (~a->digit[i] & LOMSK) + (a->digit[i-1] >> AC_SHIFT);
        a->digit[i-1] &= LOMSK;
    }
    a->digit[a->len+1] &= 0x1;
}

/*
    _naive_mul_():
        Multiply two numbers with naive method.
*/
big _naive_mul_(big a, big b) {
    big res; init(&res, a.len*2);
    lrlp(i, 1, a.len)
    lrlp(j, 1, b.len) {
        res.digit[i+j-1] += a.digit[i] * b.digit[j];
        res.digit[i+j]   += res.digit[i+j-1] >> AC_SHIFT;
        res.digit[i+j-1] &= LOMSK;
    }
    return res;
}

big _karatsuba_mul_(big a, big b) {

    printf("************ RECURSIVE CALL **************\n");
    printf("a: "); printBinary(a); printf("\n");
    printf("-- TIMES --\n");
    printf("b: "); printBinary(b); printf("\n");

    big res; init(&res, a.len*2);
    if (a.len == 1) {
        res.digit[1]  = a.digit[1] * b.digit[1];
        res.digit[2]  = res.digit[1] >> AC_SHIFT;
        res.digit[1] &= LOMSK;

        printf("Break case:  "); printBinary(res); printf("\n\n\n");
        return res;
    }

    printf("\n\n");

    int sign;
    big mul0, mul1, mul2, sub0, sub1, add1, add2, al, ah, bl, bh; 

    // Set ah, al                                                                                       
    init(&al, a.len/2); memcpy(&al.digit[1], &a.digit[1],           a.len/2*sizeof(uint64_t)); printf("al:          "); printBinary(al); printf("\n");
    init(&ah, a.len/2); memcpy(&ah.digit[1], &a.digit[a.len/2 + 1], a.len/2*sizeof(uint64_t)); printf("ah:          "); printBinary(ah); printf("\n");

    // Set bh, bl
    init(&bl, b.len/2); memcpy(&bl.digit[1], &b.digit[1],           b.len/2*sizeof(uint64_t)); printf("bl:          "); printBinary(bl); printf("\n");
    init(&bh, b.len/2); memcpy(&bh.digit[1], &b.digit[b.len/2 + 1], b.len/2*sizeof(uint64_t)); printf("bh:          "); printBinary(bh); printf("\n");

    // Get abs(ah - al), abs(bl - bh), record the sign...                             abs(sub0): 
    sub0 = sub(ah, al);                                                       printf("sub0:        "); printBinary(sub0); printf("\n");
    sub1 = sub(bl, bh);                                                       printf("sub1:        "); printBinary(sub1); printf("\n"); 
    sign = carry(sub0) ^ carry(sub1);                                         printf("sign:        %d\n", sign);
    if (sub0.digit[sub0.len+1]) neg(&sub0);                                   printf("abs(sub0):   "); printBinary(sub0); printf("\n");
    if (sub1.digit[sub1.len+1]) neg(&sub1);                                   printf("abs(sub1):   "); printBinary(sub0); printf("\n");
 
    mul0 = _karatsuba_mul_(al, bl);     memcpy(&res.digit[1],       &mul0.digit[1], a.len*sizeof(uint64_t)); 
    mul1 = _karatsuba_mul_(ah, bh);     memcpy(&res.digit[a.len+1], &mul1.digit[1], a.len*sizeof(uint64_t)); 
    mul2 = _karatsuba_mul_(sub0, sub1); if (sign) neg(&mul2);

    printf("mul0:        "); printBinary(mul0); printf("\n");
    printf("mul1:        "); printBinary(mul1); printf("\n");
    printf("mul2:        "); printBinary(mul2); printf("\n");
    printf("res+mul0-1:  "); printBinary(res); printf("\n");

    add1 = add(mul0, mul1); printf("add1:        "); printBinary(add1); printf("\n");
    add2 = add(add1, mul2); printf("add2:        "); printBinary(add2); printf("\n");

    lrlp(i, 1, a.len+1) {
        res.digit[i   + a.len/2] += add2.digit[i] + (res.digit[i-1 + a.len/2] >> AC_SHIFT);
        res.digit[i-1 + a.len/2] &= LOMSK;
    }
    lrlp(i, 3*a.len/2, a.len*2+1) {
        res.digit[i]   += res.digit[i-1] >> AC_SHIFT;
        res.digit[i-1] &= LOMSK;
    }

    assert(res.digit[res.len+1] == 0);

    printf("res:         "); printBinary(res); printf("\n");
    return res;
}


int main() {
    srand(time(NULL));

    big a; init(&a, LEN); randbig(&a, LEN);
    big b; init(&b, LEN); randbig(&b, LEN);

    big c;
    big d;
    measureTime(
        c = _karatsuba_mul_(a, b);
    );

    printf("a is "); fflush(stdout); print(a); printf("\n");
    printf("b is "); fflush(stdout); print(b); printf("\n");
    printf("c is "); fflush(stdout); print(c); printf("\n");
}