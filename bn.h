#ifndef __BIGNUM_H__
#define __BIGNUM_H__

/*
 * compile with -DSTATIC_BIT_ARRAYS for 100 digit fixed static arrays
 * or additionally with -DSET_BIT_ARRAY_SIZE=n for custom static arrays size
 */
#ifdef STATIC_BIT_ARRAYS
 #ifdef SET_BIT_ARRAY_SIZE
  #define BIT_CHUNK_SIZE SET_BIT_ARRAY_SIZE
 #else
  #define BIT_CHUNK_SIZE 100
 #endif
#else
#define BIT_CHUNK_SIZE 10
#endif

typedef char bignum_bit_t;

typedef struct {
#ifdef STATIC_BIT_ARRAYS
  bignum_bit_t d[BIT_CHUNK_SIZE];
#else
  bignum_bit_t* d;    /* pointer to array of bits */
#endif
  int neg;            /* strictly 1 or 0 */
  int digits;         /* number of digits */
  size_t alloced;     /* number of allocated bits */
} bignum_t;

bignum_t bignum_create(int number);
bignum_t bignum_create_from_string(const char* number);
bignum_t bignum_reserve(int digits);
bignum_t bignum_copy(bignum_t x, size_t reserved_size);
bignum_t bignum_set(bignum_t x, int number);

void bignum_destroy(bignum_t* x);
void bignum_destroy_multiple(int n_args, ...);

/*
 * -1 => x < y, 1 => x > y, 0 => equal
 */
int bignum_compare(bignum_t x, bignum_t y);
bignum_t bignum_negate(bignum_t x);
bignum_t bignum_add(bignum_t x, bignum_t y);
bignum_t bignum_substract(bignum_t x, bignum_t y);
bignum_t bignum_multiply(bignum_t x, bignum_t y);
bignum_t bignum_divide(bignum_t x, bignum_t y);

char* bignum_stringify(bignum_t x);

/*
 * split in half, length of head is either equal or one shorter than tail
 */
void bignum_split(bignum_t x, bignum_t* tail, bignum_t* head);
/*
 * shift left [times] times, i.e. multiply by 10^times
 */
bignum_t bignum_shift(bignum_t x, int times);
/*
 * shift right [times] times, i.e. divide by 10^times
 */
bignum_t bignum_unshift(bignum_t b, int times);

#endif
