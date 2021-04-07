#pragma once
///////////////////////////////////////////////////////////////////////////////////
//					== Written by (somewhat) Mistsu ==
//					 The Library for performing with
//		   					  Big Integers
//  Based on the code of: https://codeforces.com/contest/98/submission/3856625
//
///////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <math.h>
#include <time.h>
#include <random>
#include <iostream>
#include <cstring>
using namespace std;
typedef uint64_t uint64;

/*
	Global variables:
	[+] Bsize: size of the arrays that holds uint64 values
	[+] bl: bit-length of each array
	    In here, you could see that I only use 32 bit in the 64-bit variable.
		Just in case you don't know, the purpose is to keep the BigNum from being overflowed when performing arithmetic operations
	[+] base: the maximum value that each array cannot overcome
	[+] mlow <mask-low>: a mask to get lower 32 bits
	[+] mhigh <mask-high>: a mask to get higher 32 bits
*/
const int Bsize    = 2200;					 // size of the arrays that holds uint64 values
const int bl       = 32;					 // bit-length of each array
const uint64 base  = 0x0000000100000000;	 // the maximum value that each array cannot overcome
const uint64 mlow  = 0x00000000ffffffff;	 // a mask to get the lower 32 bits
const uint64 mhigh = 0xffffffff00000000; 	 // a mask to get the higher 32 bits

struct BigInt
{
	int len = 0;
	uint64 data[Bsize];

	inline BigInt() {
		memset(data, 0, sizeof(data));
		len = 0;
	}
	inline BigInt(const uint64& num) {
		memset(data, 0, sizeof(data));
		data[1] = num & mlow;
		data[2] = num / base;
		data[2] ? len = 2 : len = 1;
	}

	uint64 &operator[] (int x) { return data[x]; }
	const uint64 &operator[] (int x) const { return data[x]; }

	BigInt operator= (const BigInt& b) {
		for (int i = b.len + 1; i <= len; ++i) data[i] = 0;
		for (int i = 1; i <= b.len; ++i) data[i] = b[i];
		len = b.len;
		return *this;
	}
	BigInt operator= (const uint64& i64) {
		for (int i = len; i >= 0; --i) data[i] = 0; //clear
		data[1] = i64 & mlow;
		data[2] = i64 / base;
		data[2] ? len = 2 : len = 1;
		return *this;
	}

	void clear() {
		for (int i = len; i >= 1; --i) data[i] = 0;
		len = 0;
	}
	void rand(int length=1024) {
		srand(time(0));
		std::random_device rd; // seed
		std::default_random_engine generator(rd()); // random generator
		std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFF); // range

		clear(); int i = 1;
		for (; length >= bl; i++, length -= bl)
			data[i] = distribution(generator) & mlow;
		len = i + (bool)length - 1;
		while (length)
			data[i] |= (distribution(generator) % 2) << length--;
		if (!data[len]) len--;
	}
	void rand(BigInt l, BigInt r) {
		memset(data, 0, sizeof(data));
		BigInt diff = r - l;
		rand(diff.len * bl);
		(*this) = (*this) % diff + l;
	}
	void rand(uint64 l, BigInt r) {
		memset(data, 0, sizeof(data));
		BigInt diff = r - l;
		rand(diff.len * bl);
		(*this) = (*this) % diff + l;
	}

	// Comparing numbers
	int check(const BigInt &a, const BigInt &b) {
		if (a.len > b.len) return 0;
		if (b.len > a.len) return 1;
		for (int i = a.len; i >= 1; --i) {
			if (a[i] < b[i]) return 1;
			if (b[i] < a[i]) return 0;
		}
		return 2;
	}
	bool operator< (const BigInt &b) { return(check(*this, b) == 1); }
	bool operator> (const BigInt &b) { return(check(*this, b) == 0); }
	bool operator<=(const BigInt &b) { return(check(*this, b) >= 1); }
	bool operator>=(const BigInt &b) { return(check(*this, b) % 2 == 0); }
	bool operator!=(const BigInt &b) { return(check(*this, b) != 2); }
	bool operator==(const BigInt &b) { return(check(*this, b) == 2); }

	bool operator< (const uint64& num) {
		BigInt tmpNum(num);
		return(check(*this, tmpNum) == 1);
	}
	bool operator> (const uint64& num) {
		BigInt tmpNum(num);
		return(check(*this, tmpNum) == 0);
	}
	bool operator<=(const uint64& num) {
		BigInt tmpNum(num);
		return(check(*this, tmpNum) >= 1);
	}
	bool operator>=(const uint64& num) {
		BigInt tmpNum(num);
		return(check(*this, tmpNum) % 2 == 0);
	}
	bool operator!=(const uint64& num) {
		BigInt tmpNum(num);
		return(check(*this, tmpNum) != 2);
	}
	bool operator==(const uint64& num) {
		BigInt tmpNum(num);
		return(check(*this, tmpNum) == 2);
	}

	// Operators with bits
	BigInt operator<<(int x) {
		BigInt tmp; int lskip;
		lskip = x / bl;
		x %= bl;
		for (int i = len + 1; i >= 1; --i) {
			tmp[i + lskip] = data[i] << x | data[i - 1] >> (bl - x);
			tmp[i + lskip] &= mlow; // all the spare bits drive me nuts!!!!
		}
		tmp.len = len + lskip;
		if (tmp[tmp.len + 1])tmp.len++;
		return tmp;
	}
	BigInt operator>>(int x) {
		BigInt tmp; int rskip;
		rskip = x / bl;
		x %= bl;
		for (int i = 1; i <= len - rskip; ++i) {
			tmp[i] = data[i + rskip] >> x | data[i + 1 + rskip] << (bl - x);
			tmp[i] &= mlow;			// yeah, we don't want any spare bits shit around
		}
		tmp.len = max(len - rskip, 0);
		if (!tmp[tmp.len]) tmp.len--;
		return tmp;
	}
	BigInt operator| (const BigInt &b) {
		int i, l = max(len, b.len);
		for (i = 1; i <= l; ++i) data[i] |= b[i];
		len = l;
		return (*this);
	}
	BigInt operator& (const BigInt &b) {
		int i, l = max(len, b.len);
		for (i = 1; i <= l; ++i) data[i] &= b[i];
		len = l;
		return (*this);
	}

	// Arithmetics opearations
	BigInt operator- (const BigInt &b) {
		BigInt tmp;
		for (int i = 1; i <= len; ++i) tmp[i] = data[i] - b[i];
		for (int i = 1; i <= len; ++i)
			if (tmp[i] >= base) tmp[i] += base, tmp[i + 1]--;
		tmp.len = len;
		while (tmp[tmp.len] == 0 && tmp.len > 1)tmp.len--;
		return tmp;
	}
	BigInt operator+ (const BigInt &b) {
		BigInt tmp;
		int i, l = max(len, b.len);
		for (i = 1; i <= l; ++i)tmp[i] = data[i] + b[i];
		for (i = 1; i <= l; ++i)tmp[i + 1] += (tmp[i] >> bl) & mlow, tmp[i] &= mlow;
		tmp.len = l;
		if (tmp[tmp.len + 1])tmp.len++;
		return tmp;
	}
	BigInt operator% (const BigInt &b) {
		if (b.len <= 1 && b[1] == 0) {
			cerr << "[] Error module by 0." << endl;
			for (;;);	// nasty forever loop
		}
		if ((*this) < b) return (*this);

		int i, l1 = (len - 1)*bl, l2 = (b.len - 1)*bl;
		uint64 x = data[len], y = b[b.len];
		while (x) x >>= 1, l1++;
		while (y) y >>= 1, l2++;

		BigInt thi, B;
		thi = *this; B = b;
		B <<= max(l1 - l2, 0);
		for (i = l1 - l2; i >= 0; --i) {
			if (thi >= B) thi -= B;
			B >>= 1;
		}
		return thi;
	}
	BigInt operator* (const BigInt &b) {
		int i, j;
		BigInt tmp;
		for (i = 1; i <= len; ++i)if (data[i] != 0)
			for (j = 1; j <= b.len; ++j)if (b[j] != 0) {

				tmp[i + j - 1] += data[i] * b[j];
				tmp[i + j]     += (tmp[i + j - 1] >> bl) & mlow;
				tmp[i + j - 1] &= mlow;

			}
		tmp.len = len + b.len - 1;
		while (tmp[tmp.len + 1])tmp.len++;
		return tmp;
	}
	BigInt operator/ (const BigInt &b) {
		if (b.len <= 1 && b[1] == 0) {
			cerr << "[] Error division by 0." << endl;
			for (;;);	// nasty forever loop
		}
		if ((*this) < b) return 0;

		int i, l1 = (len - 1)*bl, l2 = (b.len - 1)*bl;
		uint64 x = data[len], y = b[b.len];
		while (x) x >>= 1, l1++;
		while (y) y >>= 1, l2++;

		BigInt tmp, thi, B;
		thi = *this; B = b;
		B <<= max(l1 - l2, 0);
		for (i = l1 - l2; i >= 0; --i) {
			tmp[i / bl + 1] <<= 1;
			if (thi >= B) thi -= B, tmp[i / bl + 1] |= 1;
			B >>= 1;
		}
		tmp.len = (l1 - l2) / bl + 1;
		while (tmp.len >= 1 && !tmp[tmp.len]) tmp.len--;
		return tmp;
	}


	// For processing with uint64 nums
	BigInt operator+ (const uint64& num) {
		BigInt tmpNum(num);
		return (*this + tmpNum);
	}
	BigInt operator- (const uint64& num) {
		BigInt tmpNum(num);
		return (*this - tmpNum);
	}
	BigInt operator* (const uint64& num) {
		BigInt tmpNum(num);
		return (*this * tmpNum);
	}
	BigInt operator/ (const uint64& num) {
		BigInt tmpNum(num);
		return (*this / tmpNum);
	}
	BigInt operator% (const uint64& num) {
		BigInt tmpNum(num);
		return (*this % tmpNum);
	}
	BigInt operator| (const uint64& num) {
		BigInt tmpNum(num);
		return (*this | tmpNum);
	}
	BigInt operator& (const uint64& num) {
		BigInt tmpNum(num);
		return (*this | tmpNum);
	}

	BigInt operator +=(const BigInt &b) { return *this = (*this + b); }
	BigInt operator *=(const BigInt &b) { return *this = (*this * b); }
	BigInt operator -=(const BigInt &b) { return *this = (*this - b); }
	BigInt operator /=(const BigInt &b) { return *this = (*this / b); }
	BigInt operator %=(const BigInt &b) { return *this = (*this % b); }
	BigInt operator |=(const BigInt &b) { return *this = (*this | b); }
	BigInt operator &=(const BigInt &b) { return *this = (*this & b); }

	BigInt operator +=(const uint64& num) { return *this = (*this + num); }
	BigInt operator *=(const uint64& num) { return *this = (*this * num); }
	BigInt operator -=(const uint64& num) { return *this = (*this - num); }
	BigInt operator /=(const uint64& num) { return *this = (*this / num); }
	BigInt operator %=(const uint64& num) { return *this = (*this % num); }
	BigInt operator |=(const uint64& num) { return *this = (*this | num); }
	BigInt operator &=(const uint64& num) { return *this = (*this & num); }
	BigInt operator <<=(int x) { return *this = (*this << x); }
	BigInt operator >>=(int x) { return *this = (*this >> x); }
};

BigInt pow(BigInt a, BigInt p, BigInt n) {
	BigInt ans = 1; bool bit = false;
	uint64 x;
	int i = p.len, b = bl;
	int count = 0;
	while (!bit) bit = p[i] >> --b;
	for (; i >= 1; --i) {
		x = p[i];
		for (; b >= 0; --b) {
			bit = x >> b;
			ans *= ans;
			if (bit) ans *= a;
			ans %= n;
			//cout << "[] Doing bit " << count++ << endl;
		}
		b = bl - 1;
	}
	return ans;
}

BigInt pow(BigInt bA, uint64 p, BigInt bN) {
	BigInt bP(p);
	return pow(bA, bP, bN);
}
BigInt pow(BigInt bA, uint64 p, uint64 n)
{
	BigInt bN(n), bP(p);
	return pow(bA, bP, bN);
}
BigInt pow(BigInt bA, BigInt bP, uint64 n) {
	BigInt bN(n);
	return pow(bA, bP, bN);
}
