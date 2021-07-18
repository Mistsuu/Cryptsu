#include <iostream>
#include <vector>
#include <string.h>
#include <assert.h>

#define loop(_i_, _n_)       for (int _i_ = 0;   _i_ <  (int)_n_; ++_i_)
#define lrlp(_i_, _l_, _r_)  for (int _i_ = _l_; _i_ <= (int)_r_; ++_i_)
#define rllp(_i_, _r_, _l_)  for (int _i_ = _r_; _i_ >= (int)_l_; --_i_)

using namespace std;

#define HSHIFT 32
#define BIT    32
#define LOMSK  0x00000000ffffffff
#define HIMSK  0xffffffff00000000
#define BASE   0x0000000100000000

template<int LEN>
class BigNum {
public:
    uint64_t dig[LEN+2];
///////////////////////////////////////////////////////////////////////////

    /*
        constructor(): Create BigNum!
    */
    BigNum() {
        memset(dig, 0, (LEN+2)*sizeof(uint64_t));
    }

    BigNum(BigNum& num) {
        memcpy(dig, num.dig, (LEN+2)*sizeof(uint64_t));
    }

    BigNum(const BigNum& num) {
        memcpy(dig, num.dig, (LEN+2)*sizeof(uint64_t));
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator=(): Set string to BigNum!
    */
    void operator=(string numStr) {
        lrlp(i, 0, numStr.length() - 1) {
            (*this) = (*this) * 10;
            (*this) = (*this) + (uint64_t)(numStr[i] - '0');
        }
    }

///////////////////////////////////////////////////////////////////////////

    /*
        zero(): Just zero out memory.
    */
    void zero() {
        memset(dig, 0, (LEN+2)*sizeof(uint64_t));
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator+(): Perform addtion with number!
    */
    BigNum operator+(BigNum& num) {
        BigNum res;
        // Adding with carry
        lrlp(i, 1, LEN) {
            res.dig[i]    = dig[i] + num.dig[i] + (res.dig[i-1] >> HSHIFT);
            res.dig[i-1] &= LOMSK;
        }
        return res;
    }

    BigNum operator+(uint64_t num) {
        BigNum res;
        // Adding with carry
        res.dig[1] = dig[1] + num;
        lrlp(i, 2, LEN) {
            res.dig[i]    = dig[i] + (res.dig[i-1] >> HSHIFT);
            res.dig[i-1] &= LOMSK;
        }
        return res;
    }

    void operator+=(BigNum& num) {
        // Adding with carry
        lrlp(i, 1, LEN) {
            dig[i]   += num.dig[i] + (dig[i-1] >> HSHIFT);
            dig[i-1] &= LOMSK;
        }
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator*(): Perform multiplication with number!
    */
    BigNum operator*(BigNum& num) {
        BigNum res;
        // Multiply with carry
        lrlp(i, 1, LEN) if (dig[i])
        lrlp(j, 1, LEN) if (num.dig[j]) {
            res.dig[i+j-1] += dig[i] * num.dig[j];
            res.dig[i+j]   += (res.dig[i+j-1] >> HSHIFT) & LOMSK;
            res.dig[i+j-1] &= LOMSK;
        }
        return res;
    }

    BigNum operator*(uint64_t num) {
        BigNum res;
        // Multiply with carry
        lrlp(i, 1, LEN) if (dig[i]) {
            res.dig[i]   += dig[i] * num;
            res.dig[i+1] += (res.dig[i] >> HSHIFT) & LOMSK;
            res.dig[i]   &= LOMSK;
        }
        return res;
    }


///////////////////////////////////////////////////////////////////////////

    /*
        operator-(): Subtract two big num!
    */
    BigNum operator-(BigNum& num) {
        BigNum res;
        // Subtract with carry
        lrlp(i, 1, LEN) {
            res.dig[i] += dig[i] - num.dig[i];
            if (res.dig[i] >= BASE)
                res.dig[i] += BASE, res.dig[i+1]--;
        }
        return res;
    }

    /*
        operator-(): Subtract two big num!
    */
    void operator-=(BigNum& num) {
        // Subtract with carry
        lrlp(i, 1, LEN) {
            dig[i] -= num.dig[i];
            if (dig[i] >= BASE)
                dig[i] += BASE, dig[i+1]--;
        }
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator>>(): Performs bitshift right!
    */
    BigNum operator>>(int rShift) {
        int digitShift  = rShift/BIT;
        rShift         %= BIT;

        BigNum res;
        lrlp(i, digitShift+1, LEN)
            res.dig[i-digitShift] = (dig[i] >> rShift | dig[i+1] << (BIT-rShift)) & LOMSK;
        return res;
    }

    /*
        operator>>=(): Performs bitshift right (in-place)!
    */
    void operator>>=(int rShift) {
        int digitShift  = rShift/BIT;
        rShift         %= BIT;
        lrlp(i, digitShift+1, LEN)
            dig[i-digitShift] = (dig[i] >> rShift | dig[i+1] << (BIT-rShift)) & LOMSK;
        memset(dig + LEN-digitShift+1, 0, digitShift * sizeof(uint64_t));
    }

//////////////////////////////////////////////////////////////////////////

    /*
        operator<<(): Performs bitshift left!
    */
    BigNum operator<<(int lShift) {
        int digitShift  = lShift/BIT;
        lShift         %= BIT;

        BigNum res;
        lrlp(i, 1, LEN-digitShift)
            res.dig[i+digitShift] = (dig[i] << lShift | dig[i-1] >> (BIT-lShift)) & LOMSK;
        return res;
    }

    /*
        operator<<=(): Performs bitshift left (in-place)!
    */
    void operator<<=(int lShift) {
        int digitShift  = lShift/BIT;
        lShift         %= BIT;
        rllp(i, LEN-digitShift, 1)
            dig[i+digitShift] = (dig[i] << lShift | dig[i-1] >> (BIT-lShift)) & LOMSK;
        memset(dig + 1, 0, digitShift * sizeof(uint64_t));
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator%(): Return the remainder of the division!
    */
    void operator%=(BigNum num) {
        // Checks for divised
        int i=LEN, bitI=BIT-1;
        while (i    && !  dig[i]              ) i--; if (!i) return;
        while (bitI && !((dig[i] >> bitI) & 1)) bitI--;

        // Checks for divisor
        int j=LEN, bitJ=BIT-1;
        while (j    && !  num.dig[j]              ) j--; assert(j != 0);
        while (bitJ && !((num.dig[j] >> bitJ) & 1)) bitJ--;

        // If shift bigger, go away!
        if (j > i || (j == i && bitJ > bitI))
            return;

        // Shift left so that the bits of divisor matches divised
        int initShift = (i-j)*32 + (bitI-bitJ);
        num <<= initShift;

        // Performs shifting
        loop(k, initShift + 1) {
            // Compare two numbers
            bool smaller = false;
            rllp(m, i, 1)
                if      (dig[m] < num.dig[m]) { smaller = true;  break; }
                else if (dig[m] > num.dig[m]) {                  break; }
            // Subtract if bigger
            if (!smaller)
                *this -= num;
            num >>= 1;
        }
    }

};

///////////////////////////////////////////////////////////////////////////

    /*
        opeartor<<() (for outputing): Output to stream to BigNum!
    */
    template<int LEN>
    ostream& operator<<(ostream& os, BigNum<LEN>& num) {
        rllp(i, LEN, 2)
            os << num.dig[i] << ' ';
        os << num.dig[1];
        return os;
    }

    template<int LEN>
    ostream& operator<<(ostream& os, const BigNum<LEN>& num) {
        rllp(i, LEN, 2)
            os << num.dig[i] << ' ';
        os << num.dig[1];
        return os;
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator>>() (for inputting): Input from stream to BigNum!
    */
    template<int LEN>
    istream& operator>>(istream& os, BigNum<LEN>& num) {
        string numStr;
        os >> numStr;
        num = numStr;
        return os;
    }

///////////////////////////////////////////////////////////////////////////

    /*
        pow(): Raise a BigNum to a power of BigNum! (a^b mod p)
    */
    template<int LEN>
    BigNum<LEN> pow(BigNum<LEN> a, BigNum<LEN> b, BigNum<LEN>& p) {
        // Setup
        BigNum<LEN> res;
        res.dig[1] = 1;
        a %= p;

        // Square multiple algorithm
        rllp(i, LEN, 1) if (b.dig[i])
        rllp(j, BIT - 1, 0) {
            res = res * res;
            res %= p;
            if ((b.dig[i] >> j) & 1) {
                res = res * a;
                res %= p;
            }
        }
        // Return value
        return res;
    }
