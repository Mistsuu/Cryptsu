#include "BigNum.h"

/*
    _naive_mul_():
        Multiply two numbers with naive method.
*/
big _naive_mul_(big a, big b) {
    big res; init(&res, a.len<<1);
    lrlp(i, 1, a.len)
    lrlp(j, 1, a.len) {
        res.digit[i+j-1] += a.digit[i] * b.digit[j];
        res.digit[i+j]   += (res.digit[i+j-1] >> AC_SHIFT) & LOMSK;
        res.digit[i+j-1] &= LOMSK;
    }
    return res;
}