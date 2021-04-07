#include <immintrin.h>
#include <bits/stdc++.h>
using namespace std;

int main() {
    uint64_t a[32] = {2147483647, 2147483647, 0, 0};
    uint64_t b[32] = {2147483649, 2147483649, 0, 0};
    uint64_t c[32] = {0, 0, 0, 0};
    unsigned char carry = 0;

    for (int i = 0; i < 32; ++i) {
        carry = _addcarry_u32(carry, a[i], b[i], &c[i]);
    }
}
