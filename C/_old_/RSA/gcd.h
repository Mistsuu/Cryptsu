#ifndef GCD
#define GCD

    #include <gmpxx.h>
    #include "../lib/gmpOp.h"

    big gcd_ex(big a, big b, big& x, big& y) {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }

        big x1, y1;
        big gcd = gcd_ex(b % a, a, x1, y1);

        x = y1 - (b/a) * x1;
        y = x1;

        return gcd;
    }

#endif
