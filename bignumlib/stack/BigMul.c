#include "BigNum.h"

/*
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

/*
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
