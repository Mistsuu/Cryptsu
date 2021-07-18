#pragma once
#include <iostream>
#include "BigNum.h"
using namespace std;
void test()
{
	uint32_t a[3];
	int x = 0;
	a[0] = 30020;
	a[1] = 1212494892482 + pow(2, 31);
	uint32_t lbits = (a[1] >> (32 - x)) & ((1 << x) - 1); // getting first x bytes of a[1]
	uint32_t rbits = (a[0] & ((1 << 32 - x) - 1)); // last 32- x bits of a[0]
	a[2] = rbits << x | lbits;
	//a[0] = (a[1] & ((1 << 32 - x) - 1));
	//a[0] = (-1 & ~((1 << x) - 1));
	//a[0] &= 0;


	for (int i = 31; i >= 0; --i)
		cout << ((a[1] >> i) & 1);
	cout << endl;

	for (int i = 31; i >= 0; --i)
		cout << ((a[0] >> i) & 1);
	cout << endl;
	for (int i = 31; i >= 0; --i)
		cout << ((a[2] >> i) & 1);
	cout << endl;
}
void test1()
{
	uint64_t ui = 1212494892482 + pow(2, 63);
	BigInt bi;
	bi = ui;

	for (int i = 63; i >= 0; --i)
		cout << ((ui >> i) & 1);
	cout << endl;

	for (int k = bi.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((bi[k] >> i) & 1);
		cout << endl;
	}

	bi = bi >> 32;
	for (int k = bi.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((bi[k] >> i) & 1);
		cout << endl;
	}
}
void test2()
{
	BigInt a, b;
	a = 2194809148109880;
	b = 14125185898013059809;
	BigInt c =  a | b;
	for (int k = a.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((a[k] >> i) & 1);
		cout << endl;
	}
	cout << "##########################3" << endl;
	for (int k = b.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((b[k] >> i) & 1);
		cout << endl;
	}
	cout << "##########################3" << endl;
	for (int k = c.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((c[k] >> i) & 1);
		cout << endl;
	}
}
void test3()
{
	BigInt a, b;
	a.rand();

	for (int k = a.len; k >= 1; --k) {
		for (int i = 63; i >= 0; --i)
			cout << ((a[k] >> i) & 1);
		cout << endl;
	}
	cout << endl;
}
void test4()
{
	BigInt p = generate_prime_number(1024);
	for (int k = p.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((p[k] >> i) & 1);
		//cout << endl;
	}
	cout << endl;
}
void test5()
{
	BigInt a = 1;
	BigInt b = 2304882324984023867;

	a = a * a * a;

	cout << (b == 2304882324984023867 ? "yes" : "no") << endl;
}
void test6()
{
	BigInt b;
	b.rand(1024);
	BigInt p = pow(2, b - 1, b);

	for (int k = b.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((b[k] >> i) & 1);
	//	cout << endl;
	}
	cout << endl;
	for (int k = p.len; k >= 1; --k) {
		for (int i = 31; i >= 0; --i)
			cout << ((p[k] >> i) & 1);
		cout << endl;
	}
	cout << endl;
}

void test7()
{
	
}
