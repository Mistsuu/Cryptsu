#include <iostream>
#include <gmpxx.h>
#include <sstream>
#include <fstream>
#include "genPrime.h"
#include "keyGen.h"

using namespace std;

int    argc;
char** argv;

void input(int& bits) {
    if (argc <= 1)
        exit(-1);

    stringstream input;
    for (int i = 1; i < argc; ++i)
        input << argv[i] << "\n";
    input >> bits;
}

int main(int _argc_, char** _argv_) {
    argc = _argc_;
    argv = _argv_;
    // Input no bits to generate key
    int bits;
    input(bits);
    // Generate keys
    KeyPair pubKey, privKey;
    generateKeys(pubKey, privKey, bits);
    // Output key in base 10
    cout << "[] Public:  " << pubKey.unique  << endl;
    cout << "[] Private: " << privKey.unique << endl;
    cout << "[] Common:  " << pubKey.common  << endl;
}
