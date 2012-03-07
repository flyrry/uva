
#define BIT_CHUNK_SIZE 100

typedef char bignum_bit_t;

typedef struct {
  bignum_bit_t* d;    /* pointer to array of bits */
  int neg;            /* strictly 1 or 0 */
  int digits;         /* number of digits */
  size_t alloced;     /* number of allocated bits */
} bignum_t;

bignum_t* bignum_create(int number);
bignum_t* bignum_reserve(int digits);
void bignum_destroy(bignum_t* b);
void bignum_set(bignum_t* b, int number);
bignum_t* bignum_add(bignum_t* a, bignum_t* b);
bignum_t* bignum_substract(bignum_t* a, bignum_t* b);
