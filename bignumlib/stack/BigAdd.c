#include "BigNum.h"

//  add():
//      Add 2 big numbers.
big add(big a, big b) {
    lrlp(i, 1, LEN) {
        a.digit[i]   += b.digit[i] + (a.digit[i-1] >> AC_SHIFT);
        a.digit[i-1] &= LOMSK;
    }
    a.digit[LEN] &= LOMSK;
    return a;
}