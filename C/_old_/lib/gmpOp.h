#ifndef GMP_OP
#define GMP_OP

    #include <gmpxx.h>
    #include <time.h>
    #include <fstream>
    using namespace std;

    // Define for GMP library
    typedef mpz_class big;

    // Variable for random state
    gmp_randstate_t randomState;
    bool            initRandomYet = false;

    void initRandom() {
        // Initialize random state if not intialized
        if (!initRandomYet)
            gmp_randinit_default(randomState),
            initRandomYet = true;

        // Set random seed according to /dev/random
        unsigned long int seed;
        fstream("/dev/random", fstream::in).read(reinterpret_cast<char*>(&seed), sizeof(seed));
        gmp_randseed_ui(randomState, seed | time(NULL));
    }

    /*
        pow():
            [Args:] _m_: Modulo number.
                    _a_: Base number.
                    _b_: Power number.
            [retvalue] = _a_ ** _b_ mod _m_
    */
    big pow(big _a_, big _b_, big _m_) {
        big tmp;
        mpz_powm(tmp.get_mpz_t(), _a_.get_mpz_t(), _b_.get_mpz_t(), _m_.get_mpz_t());
        return tmp;
    }

    /*
        getRandBits():
            [Args:] bits: Number of bits needed to generate.
    */
    big getRandBits(int bits) {
        // Randomize the random
        initRandom();
        // Return value
        big tmp;
        mpz_urandomb(tmp.get_mpz_t(), randomState, bits);
        return tmp;
    }

    /*
        getRandUpto():
            [Args:] bits: Number of bits needed to generate.
                    The only difference is that the n-th bit is
                    guarantee to be flipped.
    */
    big getRandUpto(int bits) {
        // Randomize the random
        initRandom();
        // Return value
        big tmp;
        mpz_rrandomb(tmp.get_mpz_t(), randomState, bits);
        return tmp;
    }

    /*
        randrange():
            [Args:] l: Left value of range.
                    r: Right value of range.
    */
    big randrange(big l, big r) {
        // Compare
        if (r < l)
            return 0;
        // Randomize
        initRandom();
        // Return value
        big tmp, diff = r - l;
        mpz_urandomm(tmp.get_mpz_t(), randomState, diff.get_mpz_t());
        return tmp + l;
    }
    
#endif
