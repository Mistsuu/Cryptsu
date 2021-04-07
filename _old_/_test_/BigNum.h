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

template<class T>
bool inRange(T l, T r, T m) {
    return m >= l && m <= r;
}

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
    BigNum operator+(BigNum num) {
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

///////////////////////////////////////////////////////////////////////////

    /*
        operator*(): Perform multiplication with number!
    */
    BigNum operator*(BigNum num) {
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
    BigNum operator-(BigNum num) {
        BigNum res;
        // Subtract with carry
        lrlp(i, 1, LEN) {
            res.dig[i] += dig[i] - num.dig[i];
            if (res.dig[i] >= BASE)
                res.dig[i] += BASE, res.dig[i+1]--;
        }
        return res;
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
    }

///////////////////////////////////////////////////////////////////////////

    /*
        operator/(); operator()%: Divides a bignum! The result is
        stored in 2 bignums:
                        [[quotient] | [remainder]]

        [Note]: The loop used in / operator and % operator are out-of sync
                in terms the number of loops for a delibrate reason that the
                quotient has to shift one last time to get the result.
    */


    /*
        operator/(): Return the quotient of the division!
    */
    BigNum operator/(BigNum num) {
        BigNum quo(*this), rem;
        BigNum tmp; tmp.dig[LEN+1] = 1;
        loop(i, BIT * LEN + 1) {
            // Shift remainder
            rem <<= 1;
            // Shift last bit of quotient to remainder
            rem.dig[1] |= quo.dig[LEN] >> (BIT-1);
            // Shift quotient to the left
            quo <<= 1;
            quo.dig[1] |= ~tmp.dig[LEN+1] & 1;
            // Perform subtraction
            tmp = rem - num;
            // Copy to rem if subtraction is good...
            if (!tmp.dig[LEN+1])
                memcpy(rem.dig, tmp.dig, (LEN+2)*sizeof(uint64_t));
        }
        return quo;
    }

    /*
        operator%(): Return the remainder of the division!
    */
    BigNum operator%(BigNum num) {
        BigNum quo(*this), rem;
        BigNum tmp; tmp.dig[LEN+1] = 1;
        loop(i, BIT * LEN) {
            // Shift remainder
            rem = rem << 1;
            // Shift last bit of quotient to remainder
            rem.dig[1] |= quo.dig[LEN] >> (BIT-1);
            // Shift quotient to the left
            quo = quo << 1;
            quo.dig[1] |= ~tmp.dig[LEN+1] & 1;
            // Perform subtraction
            tmp = rem - num;
            // Copy to rem if subtraction is good...
            if (!tmp.dig[LEN+1])
                rem = tmp;
        }
        return rem;
    }


///////////////////////////////////////////////////////////////////////////

    /*
        set(): Set a number to BigNum!
    */
    void set(string numStr) {
        // Set memory
        uint64_t base, tmp_dig;

        // Check validity of input & set base
        if      (numStr[0] == '0' && numStr[1] == 'x') base = 16;
        else if (numStr[0] == '0' && numStr[1] == 'b') base = 2;
        else if (numStr[0] == '0' && numStr[1] == 'd') base = 10;
        else assert(false);

        // Extract digits from string
        lrlp(i, 2, numStr.length() - 1) {
            if (inRange('a', 'f', numStr[i]))
                 tmp_dig = numStr[i] - 'a' + 10;
            else tmp_dig = numStr[i] - '0';
            (*this) = (*this) * base;
            (*this) = (*this) + tmp_dig;
        }
    }

///////////////////////////////////////////////////////////////////////////

    /*
        print(): Print number!
    */
    void print() {
        rllp(i, LEN, 1)
            cout << dig[i] << " ";
        cout << endl;
    }
};
