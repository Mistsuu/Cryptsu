#include <iostream>
#include <string.h>
#include <chrono>

#define LEN 8192/32

using namespace std;

struct big_stack {
    int stack[LEN];
};

struct big_heap {
    int *heap;
};

#define measureTime( tstFunc ) do {                        \
    auto start = chrono::high_resolution_clock::now();     \
    tstFunc                                                \
    auto stop  = chrono::high_resolution_clock::now();     \
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); \
    cerr << duration.count() << " ";      \
} while(0)    

big_stack set_stack(big_stack bs) {
    for (int i = 0; i < LEN; ++i) {
        bs.stack[i] = i;
    }
    return bs;
}

big_heap set_heap(big_heap bh) {
    for (int i = 0; i < LEN; ++i) {
        bh.heap[i] = i;
    }
    return bh;
}

int main() {
    big_stack bs, bsr;
    big_heap  bh, bhr;
    bh.heap = (int*) malloc(sizeof(int) * LEN);

    measureTime(
        bsr = set_stack(bs);
    );

    measureTime(
        bhr = set_heap(bh);
    );
}