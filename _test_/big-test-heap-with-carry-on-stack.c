#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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
#define LEN    8192/16                  // Length of the array in big number.
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
    for (int i = 63; i >= 0; --i) {
        printf(ui >> i & 0x1 ? "1":"0");
    }
}

void pi(uint64_t ui) {
    printf("%lu", ui);
}

void print(big a) {
    char buf[10000]; memset(buf, 0, sizeof(buf));
    strcpy(buf, "python3 -c \"print(");
    lrlp(i, 1, LEN) {
        char term[50]; memset(term, 0, sizeof(term));
        sprintf(term, "%lu*2**%d+", a.digit[i], (i-1)*32);        
        strcat(buf, term);
    }
    strcat(buf, "0, end='')\"");
    system(buf);
}

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

//  add():
//      Add 2 big numbers.
big add(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len) {
        c.digit[i]    = a.digit[i] + b.digit[i] + (c.digit[i-1] >> AC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    c.digit[c.len] &= LOMSK;
    return c;
}

//  sub():
//      Subtract 2 big numbers.
big sub(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len) {
        c.digit[i]    = a.digit[i] - b.digit[i] - (c.digit[i-1] >> SC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    c.digit[c.len] &= LOMSK;
    return c;
}

/*
    _lowhalf_mul_():
        Multiply two low halfs of two numbers.
*/
big _lowhalf_mul_(big a, big b) {
    big res; init(&res, a.len);
    lrlp(i, 1, a.len>>1)
    lrlp(j, 1, a.len>>1) {
        res.digit[i+j-1] += a.digit[i] * b.digit[j];
        res.digit[i+j]   += (res.digit[i+j-1] >> AC_SHIFT) & LOMSK;
        res.digit[i+j-1] &= LOMSK;
    }
    return res;
}

/*
    _naive_mul_():
        Multiply two numbers, generating answer mod 2**(LEN*32)
*/
big _naive_mul_(big a, big b) {
    big res; init(&res, a.len);
    lrlp(k, 1, a.len) {   
        res.digit[k+1] += (res.digit[k] >> AC_SHIFT) & LOMSK;
        res.digit[k]   &= LOMSK;
        lrlp(i, 1, k) {
            res.digit[k]   += a.digit[i] * b.digit[k+1-i];
            res.digit[k+1] += (res.digit[k] >> AC_SHIFT) & LOMSK; 
            res.digit[k]   &= LOMSK;
        }
    }
    return res;
}


big _karatsuba_mul_(uint64_t* a_digit, uint64_t* b_digit, int size) {

}


int main() {
    srand(time(NULL));

    big a; init(&a, LEN); randbig(&a, LEN);
    big b; init(&b, LEN); randbig(&b, LEN);

    printf("a is "); fflush(stdout); print(a); printf("\n");
    printf("b is "); fflush(stdout); print(b); printf("\n");

    big c;
    measureTime(
        c = add(a, b);
    );
    printf("c is "); fflush(stdout); print(c); printf("\n");
}