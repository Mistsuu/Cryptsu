#include "BigNum.h"

//  sub():
//      Subtract 2 big numbers.
big sub(big a, big b) {
    big c; init(&c, a.len);
    lrlp(i, 1, a.len+1) {
        c.digit[i]    = a.digit[i] - b.digit[i] - (c.digit[i-1] >> SC_SHIFT);
        c.digit[i-1] &= LOMSK;
    }
    return c;
}
