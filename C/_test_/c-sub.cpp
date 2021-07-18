#include <iostream>

using namespace std;

int main() {
    int a = 8290;
    int b = 27;

    int c = -1;
    c = c >> (3 & 0x1);
    for (int i = 31; i >= 0; --i) {
        cout << ((c >> i) & 0x1 ? "1" : "0");
    }
    cout << endl;

    int d = 0x10000;
    for (int i = 31; i >= 0; --i) {
        cout << (((c + d) >> i) & 0x1 ? "1" : "0");
    }
    cout << endl;
}