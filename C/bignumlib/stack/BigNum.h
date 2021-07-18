#include <stdint.h>

/*
    Shorthand defitions for loop commands
*/
#define loop(_i_, _n_)       for (int _i_ = 0;   _i_ <  (int)_n_; ++_i_)
#define lrlp(_i_, _l_, _r_)  for (int _i_ = _l_; _i_ <= (int)_r_; ++_i_)
#define rllp(_i_, _r_, _l_)  for (int _i_ = _r_; _i_ >= (int)_l_; --_i_)

/*
    Variable definitons
*/
#define LEN      128
// Shift values that are commonly used
#define AC_SHIFT 32                         // To get addition carry bit
#define SC_SHIFT 63                         // To get subtraction carry bit
// Mask values that are commonly used
#define LOMSK  0x00000000ffffffff
#define HIMSK  0xffffffff00000000
#define BASE   0x0000000100000000

/*
    Struct
*/
typedef struct _big_ {
    uint64_t digit[LEN+2];
} big;

/*
    Functions
*/
void zero(big* a);
void str2big(big* a, char* str);
void big2str(big* a, char* str);
big add(big a, big b);
big sub(big a, big b);
big mul(big a, big b);
big div(big a, big b);
big exp(big a, big b);