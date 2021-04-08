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
#define LEN      128                // Length of the array in big number.
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

/*  
    init():
        Initialize the big number.
*/
void init(big* a, int len) {
    a->len   = len;
    a->digit = (uint64_t*) calloc(len+2, sizeof(uint64_t));
}

/*  
    randbig():
        Fills <size> digits of big number with random data.
*/
void randbig(big* a, int size) {
    lrlp(i, 1, size)
        a->digit[i] = rand() & LOMSK;
}

#define carry(a) a.digit[a.len+1]

/*  
    add():
        Add 2 big numbers to result a new big number allocated in the heap.

    [Args]
        - a: An input big number.
        - b: An input big number.
*/
big add(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len+1) {
        c.digit[i]    = a.digit[i] + b.digit[i] + (c.digit[i-1] >> AC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    c.digit[a.len+1] &= 0x1;
    return c;
}

/*  
    sub():
        Subtract 2 big numbers.
        
    [Args]
        - a: An input big number.
        - b: An input big number.
*/
big sub(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len+1) {
        c.digit[i]    = a.digit[i] - b.digit[i] - (c.digit[i-1] >> SC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    c.digit[a.len+1] &= 0x1;
    return c;
}

/*  
    neg():
        Convert a big number x to -x.

    [Args]
        - a: An input big number.
*/
void neg(big* a) {
    a->digit[0] = BASE;
    lrlp(i, 1, a->len+1) {
        a->digit[i]    = (~a->digit[i] & LOMSK) + (a->digit[i-1] >> AC_SHIFT);
        a->digit[i-1] &= LOMSK;
    }
    a->digit[a->len+1] &= 0x1;
}

/*
    naive_mul():
        Multiply two numbers with naive method.
    
    [Args]
        - a: An input big number.
        - b: An input big number.

    [Ret]
        The product of two numbers.
*/
big naive_mul(big a, big b) {
    big res; init(&res, a.len*2);
    lrlp(i, 1, a.len)
    lrlp(j, 1, b.len) {
        res.digit[i+j-1] += a.digit[i] * b.digit[j];
        res.digit[i+j]   += res.digit[i+j-1] >> AC_SHIFT;
        res.digit[i+j-1] &= LOMSK;
    }
    return res;
}

/*
    karatsuba_mul():
        Multiply two numbers with the Karatsuba method.

    [Args]
        - a: An input big number.
        - b: An input big number.

    [Ret]
        The product of two numbers.
*/
big karatsuba_mul(big a, big b) {
    big res; init(&res, a.len*2);
    if (a.len == 1) {
        res.digit[1]  = a.digit[1] * b.digit[1];
        res.digit[2]  = res.digit[1] >> AC_SHIFT;
        res.digit[1] &= LOMSK;
        return res;
    }

    int sign;
    big mul0, mul1, mul2, sub0, sub1, add1, add2, al, ah, bl, bh; 

    // Initialize al, ah, bl, bh                                                                                    
    init(&al, a.len/2); 
    init(&ah, a.len/2); 
    init(&bl, b.len/2); 
    init(&bh, b.len/2); 

    // Copy memory of the variables 
    // (could be optimised in the near future 
    // by using pointers instead of copying
    // the whole memory array)
    memcpy(&al.digit[1], &a.digit[1],           a.len/2*sizeof(uint64_t));
    memcpy(&ah.digit[1], &a.digit[a.len/2 + 1], a.len/2*sizeof(uint64_t));
    memcpy(&bl.digit[1], &b.digit[1],           b.len/2*sizeof(uint64_t));
    memcpy(&bh.digit[1], &b.digit[b.len/2 + 1], b.len/2*sizeof(uint64_t));

    // Get abs(ah - al), abs(bl - bh), record the sign...
    sub0 = sub(ah, al);                                                      
    sub1 = sub(bl, bh);                                                      
    sign = carry(sub0) ^ carry(sub1);                                        
    if (sub0.digit[sub0.len+1]) neg(&sub0);                                  
    if (sub1.digit[sub1.len+1]) neg(&sub1);                                  
    
    // Calculating the recursive multiplications
    mul0 = karatsuba_mul(al, bl);     memcpy(&res.digit[1],       &mul0.digit[1], a.len*sizeof(uint64_t)); 
    mul1 = karatsuba_mul(ah, bh);     memcpy(&res.digit[a.len+1], &mul1.digit[1], a.len*sizeof(uint64_t)); 
    mul2 = karatsuba_mul(sub0, sub1); if (sign) neg(&mul2);

    // Adding the multiplications to get the middle term
    add1 = add(mul0, mul1);
    add2 = add(add1, mul2);

    lrlp(i, 1, a.len+1) {
        res.digit[i   + a.len/2] += add2.digit[i] + (res.digit[i-1 + a.len/2] >> AC_SHIFT);
        res.digit[i-1 + a.len/2] &= LOMSK;
    }
    lrlp(i, 3*a.len/2+1, a.len*2+1) {
        res.digit[i]   += res.digit[i-1] >> AC_SHIFT;
        res.digit[i-1] &= LOMSK;
    }

    return res;
}


int main() {
    srand(time(NULL));

    big a; init(&a, LEN); randbig(&a, LEN);
    big b; init(&b, LEN); randbig(&b, LEN);

    printf("a is "); fflush(stdout); print(a); printf("\n");
    printf("b is "); fflush(stdout); print(b); printf("\n");

    big c;
    measureTime(
        c = karatsuba_mul(a, b);
    );

    printf("c is "); fflush(stdout); print(c); printf("\n");
}