#pragma once
#include "BigNum.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		  == NOT BY MISTSU AT ALL ==
//		 The library used to generate
//                  primes
//  Based on the Python code of: https://medium.com/@prudywsh/how-to-generate-big-prime-numbers-miller-rabin-49e6e6af32fb
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	Purpose:
	[?] Just like it's name, the purpose is to check if a number is prime

	Args:
	[+] n: number to test
	[+]	test: number of tests
*/
bool is_prime(BigInt n, int test = 128)
{
	int s = 0, j = 1;
	BigInt r = n - 1;
	BigInt a, x;

	while ((r[1] & 1) == 0) {
		s++;
		r = r >> 1;
	}
	//cout << s << endl;

	for (int i = 0; i < test; ++i) {
		a.rand(2, n - 1);
		x = pow(a, r, n);
		if (x != 1 && x != n - 1) {
			j = 1;
			while (j < s && x != n - 1) {
				x = (x * x) % n;
				if (x == 1) { return false; }
				j++;
			}
			if (x != n - 1) return false;
		}
	}
	return true;
}

/*
	Purpose:
	[?] Just generate some random number with <length> bits

	Args:
	[+] length: number of maximum bits in the number
*/
BigInt generate_prime_candidate(int length = 1024)
{
	BigInt p; p.rand(length);
	BigInt one = 1;
	BigInt m = (one << length - 1) | 1;
	p |= m;
	return p;
}

/*
	Purpose:
	[?] Generating a number that could possibly be "prime"

	Args:
	[+] length: number of bits needed to generate
*/
BigInt generate_prime_number(int length = 1024)
{
	BigInt p = 4;
	int i = 0;
	while (!is_prime(p, 128)) {
		//cout << p.len << endl;
		cout << "[] Test number " << ++i << "..." << endl;
		p = generate_prime_candidate(length);
	}
	return p;
}
