#include <iostream>
#include <chrono>

using namespace std;

#define measureTime( tstFunc ) do {                        \
    auto start = chrono::high_resolution_clock::now();     \
    tstFunc                                                \
    auto stop  = chrono::high_resolution_clock::now();     \
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); \
    cerr << duration.count() << " ";      \
} while(0)    

struct data {
    int d0;
int d1;
int d2;
int d3;
int d4;
int d5;
int d6;
int d7;
int d8;
int d9;
int d10;
int d11;
int d12;
int d13;
int d14;
int d15;
int d16;
int d17;
int d18;
int d19;
int d20;
int d21;
int d22;
int d23;
int d24;
int d25;
int d26;
int d27;
int d28;
int d29;
int d30;
int d31;
int d32;
int d33;
int d34;
int d35;
int d36;
int d37;
int d38;
int d39;
int d40;
int d41;
int d42;
int d43;
int d44;
int d45;
int d46;
int d47;
int d48;
int d49;
int d50;
int d51;
int d52;
int d53;
int d54;
int d55;
int d56;
int d57;
int d58;
int d59;
int d60;
int d61;
int d62;
int d63;
int d64;
int d65;
int d66;
int d67;
int d68;
int d69;
int d70;
int d71;
int d72;
int d73;
int d74;
int d75;
int d76;
int d77;
int d78;
int d79;
int d80;
int d81;
int d82;
int d83;
int d84;
int d85;
int d86;
int d87;
int d88;
int d89;
int d90;
int d91;
int d92;
int d93;
int d94;
int d95;
int d96;
int d97;
int d98;
int d99;

};

struct data2 {
    int d[100];
};

data add(data a, data b) {
    a.d0+= b.d0;
a.d1+= b.d1;
a.d2+= b.d2;
a.d3+= b.d3;
a.d4+= b.d4;
a.d5+= b.d5;
a.d6+= b.d6;
a.d7+= b.d7;
a.d8+= b.d8;
a.d9+= b.d9;
a.d10+= b.d10;
a.d11+= b.d11;
a.d12+= b.d12;
a.d13+= b.d13;
a.d14+= b.d14;
a.d15+= b.d15;
a.d16+= b.d16;
a.d17+= b.d17;
a.d18+= b.d18;
a.d19+= b.d19;
a.d20+= b.d20;
a.d21+= b.d21;
a.d22+= b.d22;
a.d23+= b.d23;
a.d24+= b.d24;
a.d25+= b.d25;
a.d26+= b.d26;
a.d27+= b.d27;
a.d28+= b.d28;
a.d29+= b.d29;
a.d30+= b.d30;
a.d31+= b.d31;
a.d32+= b.d32;
a.d33+= b.d33;
a.d34+= b.d34;
a.d35+= b.d35;
a.d36+= b.d36;
a.d37+= b.d37;
a.d38+= b.d38;
a.d39+= b.d39;
a.d40+= b.d40;
a.d41+= b.d41;
a.d42+= b.d42;
a.d43+= b.d43;
a.d44+= b.d44;
a.d45+= b.d45;
a.d46+= b.d46;
a.d47+= b.d47;
a.d48+= b.d48;
a.d49+= b.d49;
a.d50+= b.d50;
a.d51+= b.d51;
a.d52+= b.d52;
a.d53+= b.d53;
a.d54+= b.d54;
a.d55+= b.d55;
a.d56+= b.d56;
a.d57+= b.d57;
a.d58+= b.d58;
a.d59+= b.d59;
a.d60+= b.d60;
a.d61+= b.d61;
a.d62+= b.d62;
a.d63+= b.d63;
a.d64+= b.d64;
a.d65+= b.d65;
a.d66+= b.d66;
a.d67+= b.d67;
a.d68+= b.d68;
a.d69+= b.d69;
a.d70+= b.d70;
a.d71+= b.d71;
a.d72+= b.d72;
a.d73+= b.d73;
a.d74+= b.d74;
a.d75+= b.d75;
a.d76+= b.d76;
a.d77+= b.d77;
a.d78+= b.d78;
a.d79+= b.d79;
a.d80+= b.d80;
a.d81+= b.d81;
a.d82+= b.d82;
a.d83+= b.d83;
a.d84+= b.d84;
a.d85+= b.d85;
a.d86+= b.d86;
a.d87+= b.d87;
a.d88+= b.d88;
a.d89+= b.d89;
a.d90+= b.d90;
a.d91+= b.d91;
a.d92+= b.d92;
a.d93+= b.d93;
a.d94+= b.d94;
a.d95+= b.d95;
a.d96+= b.d96;
a.d97+= b.d97;
a.d98+= b.d98;
a.d99+= b.d99;


    return a;
}

data operator+ (data a, data b) {
    a.d0+= b.d0;
a.d1+= b.d1;
a.d2+= b.d2;
a.d3+= b.d3;
a.d4+= b.d4;
a.d5+= b.d5;
a.d6+= b.d6;
a.d7+= b.d7;
a.d8+= b.d8;
a.d9+= b.d9;
a.d10+= b.d10;
a.d11+= b.d11;
a.d12+= b.d12;
a.d13+= b.d13;
a.d14+= b.d14;
a.d15+= b.d15;
a.d16+= b.d16;
a.d17+= b.d17;
a.d18+= b.d18;
a.d19+= b.d19;
a.d20+= b.d20;
a.d21+= b.d21;
a.d22+= b.d22;
a.d23+= b.d23;
a.d24+= b.d24;
a.d25+= b.d25;
a.d26+= b.d26;
a.d27+= b.d27;
a.d28+= b.d28;
a.d29+= b.d29;
a.d30+= b.d30;
a.d31+= b.d31;
a.d32+= b.d32;
a.d33+= b.d33;
a.d34+= b.d34;
a.d35+= b.d35;
a.d36+= b.d36;
a.d37+= b.d37;
a.d38+= b.d38;
a.d39+= b.d39;
a.d40+= b.d40;
a.d41+= b.d41;
a.d42+= b.d42;
a.d43+= b.d43;
a.d44+= b.d44;
a.d45+= b.d45;
a.d46+= b.d46;
a.d47+= b.d47;
a.d48+= b.d48;
a.d49+= b.d49;
a.d50+= b.d50;
a.d51+= b.d51;
a.d52+= b.d52;
a.d53+= b.d53;
a.d54+= b.d54;
a.d55+= b.d55;
a.d56+= b.d56;
a.d57+= b.d57;
a.d58+= b.d58;
a.d59+= b.d59;
a.d60+= b.d60;
a.d61+= b.d61;
a.d62+= b.d62;
a.d63+= b.d63;
a.d64+= b.d64;
a.d65+= b.d65;
a.d66+= b.d66;
a.d67+= b.d67;
a.d68+= b.d68;
a.d69+= b.d69;
a.d70+= b.d70;
a.d71+= b.d71;
a.d72+= b.d72;
a.d73+= b.d73;
a.d74+= b.d74;
a.d75+= b.d75;
a.d76+= b.d76;
a.d77+= b.d77;
a.d78+= b.d78;
a.d79+= b.d79;
a.d80+= b.d80;
a.d81+= b.d81;
a.d82+= b.d82;
a.d83+= b.d83;
a.d84+= b.d84;
a.d85+= b.d85;
a.d86+= b.d86;
a.d87+= b.d87;
a.d88+= b.d88;
a.d89+= b.d89;
a.d90+= b.d90;
a.d91+= b.d91;
a.d92+= b.d92;
a.d93+= b.d93;
a.d94+= b.d94;
a.d95+= b.d95;
a.d96+= b.d96;
a.d97+= b.d97;
a.d98+= b.d98;
a.d99+= b.d99;


    return a;
}

data2 add(data2 a, data2 b) {
    for (int i = 0; i < 100; ++i) {
        a.d[i] += b.d[i];
    }
    return a;
}

data2 operator+ (data2 a, data2 b) {
    for (int i = 0; i < 100; ++i) {
        a.d[i] += b.d[i];
    }
    return a;
}


int main() {
    data a = {1, 2};
    data b = {3, 4};
    data c;
    data d;

    data2 e = {1, 2};
    data2 f = {3, 4};
    data2 g;
    data2 h;

    measureTime(
        c = a + b;
    );

    measureTime(
        d = add(a, b);
    );

    measureTime(
        g = e + f;
    );

    measureTime(
        h = add(e, f);
    );

    cout << endl;
}