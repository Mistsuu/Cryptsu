#include <stdint.h>

// --------------- For writing short loop code --------------
#define loop(_i_, _n_)       for (int _i_ = 0;   _i_ <  (int)_n_; ++_i_)
#define lrlp(_i_, _l_, _r_)  for (int _i_ = _l_; _i_ <= (int)_r_; ++_i_)
#define rllp(_i_, _r_, _l_)  for (int _i_ = _r_; _i_ >= (int)_l_; --_i_)

// ---------------------  Constants -------------------------
// Shift values that are commonly used
#define AC_SHIFT 32                         // To get addition carry bit
#define SC_SHIFT 63                         // To get subtraction carry bit
// Mask values that are commonly used
#define LOMSK  0x00000000ffffffff
#define HIMSK  0xffffffff00000000
#define BASE   0x0000000100000000

// ------------ BigNum struct that defines life! ------------
typedef struct _big_ {
    int       len;
    uint64_t *digit;
} big;

// ------------- Operations on the BigNum --------------------
void init(big* a, int len);
void str2big(big* a, char* str);
void big2str(big* a, char* str);
big add(big a, big b);
big sub(big a, big b);
big mul(big a, big b);
big div(big a, big b);
big exp(big a, big b);