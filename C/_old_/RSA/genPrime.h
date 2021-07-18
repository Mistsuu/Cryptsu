#ifndef GEN_PRIME
#define GEN_PRIME

    #include <gmpxx.h>
    #include "../lib/gmpOp.h"

    /*
        isPrime(): Test if number is a prime.
        [Args:] n:     Number to test.
                tests: The number of tests to assure that <num> is
                a prime.
    */
    bool isPrime(big n, int tests=128) {
        // Test some obvious cases
        if (n == 2 || n == 3)
            return true;
        if (n <= 1 || n % 2 == 0)
            return false;
        // Find r & s...
        big s = 0;
        big r = n - 1;
        while ((r & 1) == 0) {
            s += 1,
            r /= 2;
        }
        // Do tests...
        for (int i = 0; i < tests; ++i) {
            big a = randrange(2, n - 1);
            big x = pow(a, r, n);
            if (x != 1 && x != n - 1) {
                //
                big j = 1;
                while (j < s && x != n - 1) {
                    x = pow(x, 2, n);
                    if (x == 1)
                        return false;
                    j++;
                }
                //
                if (x != n - 1)
                    return false;
            }
        }
        return true;
    }

    /*
        generatePrimeNumber(): Create a prime number!
            [Args:] len: Length of prime number generated.
    */
    big generatePrimeNumber(int len) {
        big p;
        do {
            p = getRandUpto(len);
        } while (!(isPrime(p)));
        return p;
    }

#endif
