#include <iostream>
#include <chrono>

using namespace std;

#define measureTime( tstFunc ) do {                        \
    auto start = chrono::high_resolution_clock::now();     \
    tstFunc                                                \
    auto stop  = chrono::high_resolution_clock::now();     \
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); \
    cerr << "[] Time taken to run: " << duration.count() << "ns" << endl;      \
} while(0)    

int main() {
    int array[256001];
    int i;

    measureTime(
        for (i = 0; i < 256001; ++i)
            array[i] = i;
    );
}