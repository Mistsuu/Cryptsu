#include "BigNum.h"
#include <bits/stdc++.h>

#define measureTime( tstFunc ) do {                        \
    auto start = chrono::high_resolution_clock::now();     \
    tstFunc                                                \
    auto stop  = chrono::high_resolution_clock::now();     \
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); \
    cout << duration.count() << endl;      \
} while(0)

// cerr << "[] Time taken to run: " << duration.count() << "ns" << endl;


using namespace std;

int main() {
    BigNum<8> b, d, c;
    b.set("0d1844674408229948620936890346864806406806806480683689068340638064306843");
    d.set("0d18446744062859023890238502905289502508525028502850289414584322");
    b.print();
    d.print();
    measureTime(c = b/d;);
    c.print();
    cout << "#\n";
}
