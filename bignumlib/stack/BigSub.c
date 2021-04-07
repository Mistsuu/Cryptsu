#include "BigNum.h"

//  sub():
//      Subtract 2 big numbers.
big sub(big a, big b) {
    lrlp(i, 1, LEN) {
        a.digit[i]   -= b.digit[i] + (a.digit[i-1] >> SC_SHIFT);
        a.digit[i-1] &= LOMSK;
    }
    a.digit[LEN] &= LOMSK;
    return a;
}