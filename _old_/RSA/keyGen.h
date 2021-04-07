#ifndef KEY_GEN
#define KEY_GEN

    #include "genPrime.h"
    #include "gcd.h"
    #include "../lib/gmpOp.h"

    struct KeyPair {
        big unique;
        big common;
    };

    /*
        genEncrypt():
            We need to find e that:
                e is coprime with N and O,
                or GCD(e, N) = 1 and GCD(e, O) = 1.
    */
    big genEncrypt(big& O, big& N) {
        big e;
        do {
            e = randrange(2, O);
        } while (gcd(e, N) != 1 || gcd(e, O) != 1);
        return e;
    }

    /*
        getDecrypt():
            Find d such a way that:
                de = 1 (mod O)
            Or:
                de + Oy = 1

            Since 1 = GCD(O, e), we could achieve this by using
            Euclidean algorithm for extended GCD. In other word,
            we need to find e and y such that:
                de + Oy = GCD(O, e) = 1
    */
    big genDecrypt(big& e, big& O) {
        big d, y;
        gcd_ex(e, O, d, y);
        if (d < 0 || d == e)
            d += O;
        return d;
    }

    /*
        generateKeys():
            Generates private and public keys, each contains a common
            number and a unique number.
    */
    void generateKeys(KeyPair& pubKey, KeyPair& privKey, int bits=1024) {
        // Generate two primes
        big p = generatePrimeNumber(bits/2);
        big q;
        do {
            q = generatePrimeNumber(bits/2);
        } while (p == q);

        // Create first half
        big N = p*q;            // First number in pair, appears in both keys.
        pubKey.common = privKey.common = N;

        // Create second half
        big O = (p-1)*(q-1);    // Phi(N), for generating another halves of 2 keys.
        pubKey.unique  = genEncrypt(O, N);
        privKey.unique = genDecrypt(pubKey.unique, O);
    }

#endif
