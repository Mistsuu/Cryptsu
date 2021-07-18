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
#define LEN    8192/32                  // Length of the array in big number.
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
    uint64_t digit[LEN+2];
} big;

// void pb(uint64_t ui) {
//     for (int i = 63; i >= 0; --i) {
//         printf(ui >> i & 0x1 ? "1":"0");
//     }
// }

// void pi(uint64_t ui) {
//     printf("%lu", ui);
// }

/* ------------------------------------------------------------------------------
    zero():
        Initialize the big number to 0.
*/   
void zero(big* a) {
    memset(a, 0, (LEN+1) * sizeof(uint64_t));
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

void randbig(big* a, int size) {
    lrlp(i, 1, size) {
        a->digit[i] = rand() & LOMSK;
        //a->digit[i] = 0xffffffff;
    }
}

/* ------------------------------------------------------------------------------
    add():
        Add 2 big numbers.
*/      
big add(big a, big b) {
    lrlp(i, 1, LEN+1) {
        a.digit[i]   += b.digit[i] + (a.digit[i-1] >> AC_SHIFT);
        a.digit[i-1] &= LOMSK;
    }
    return a;
}

/* ------------------------------------------------------------------------------
    sub():
        Subtract 2 big numbers.
*/     
big sub(big a, big b) {
    lrlp(i, 1, LEN+1) {
        a.digit[i]   -= b.digit[i] + (a.digit[i-1] >> SC_SHIFT);
        a.digit[i-1] &= LOMSK;
    }
    return a;
}

/* ------------------------------------------------------------------------------
    _lowhalf_mul_():
        Multiply two low halfs of two numbers.
*/
big _lowhalf_mul_(big a, big b) {
    big res; zero(&res);
    lrlp(i, 1, LEN>>1)
    lrlp(j, 1, LEN>>1) {
        res.digit[i+j-1] += a.digit[i] * b.digit[j];
        res.digit[i+j]   += (res.digit[i+j-1] >> AC_SHIFT) & LOMSK;
        res.digit[i+j-1] &= LOMSK;
    }
    return res;
}

/* ------------------------------------------------------------------------------
    _naive_mul_():
        Multiply two numbers, generating answer mod 2**(LEN*32)
*/
big _naive_mul_(big a, big b) {
    big res; zero(&res);
    lrlp(k, 1, LEN) {   
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

/* ------------------------------------------------------------------------------
*/
big _karatsuba_mul_(big a, big b, int size) {
    big first;
}


int main() {
    srand(time(NULL));

    big a; zero(&a); randbig(&a, LEN);
    big b; zero(&b); randbig(&b, LEN);

    big c;
    measureTime(
        c = _naive_mul_(a, b);
    );

    fflush(stdout);
    printf("a is "); fflush(stdout); print(a); printf("\n");
    printf("b is "); fflush(stdout); print(b); printf("\n");
    printf("c is "); fflush(stdout); print(c); printf("\n");
}