#ifndef __BIGNUM_H__
#define __BIGNUM_H__
#define BIT_CHUNK_SIZE 10

typedef char bignum_bit_t;

typedef struct {
  bignum_bit_t* d;    /* pointer to array of bits */
  int neg;            /* strictly 1 or 0 */
  int digits;         /* number of digits */
  size_t alloced;     /* number of allocated bits */
} bignum_t;

bignum_t bignum_create(int number);
bignum_t bignum_create_from_string(char* str);
bignum_t bignum_reserve(int digits);
bignum_t bignum_copy(bignum_t b, size_t reserved_size);
bignum_t bignum_set(bignum_t b, int number);

void bignum_destroy(bignum_t* b);
void bignum_destroy_multiple(int n_args, ...);

bignum_t bignum_negate(bignum_t b);
/* -1 => a < b, 1 => a > b, 0 => equal */
int bignum_compare(bignum_t a, bignum_t b);
bignum_t bignum_add(bignum_t a, bignum_t b);
bignum_t bignum_substract(bignum_t a, bignum_t b);
bignum_t bignum_multiply(bignum_t x, bignum_t y);

const char* bignum_stringify(bignum_t b);
bignum_t bignum_pad(bignum_t b, size_t length, bignum_bit_t digit);

/*
 * remove for lib version
 */
void bignum_split(bignum_t b, bignum_t* p1, bignum_t* p2);
bignum_t bignum_shift(bignum_t b, int times);

#endif
