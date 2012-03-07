#include <stdio.h>
#include <stdlib.h>
#include "bn.h"

/*
 * remove for lib version
 */
void ppb(bignum_t* b)
{
  int i;
  if (b->neg)
    printf("-");
  for (i = b->digits - 1; i >= 0; --i)
    printf("%d", b->d[i]);
  printf("\n");
}
/*
 * remove for lib version
 */

bignum_t* bignum_create(int number)
{
  bignum_t* b = bignum_reserve(BIT_CHUNK_SIZE);
  bignum_set(b, number);
  return b;
}

bignum_t* bignum_reserve(int digits)
{
  if (digits <= 0) return NULL;
  bignum_t* b = (bignum_t*) calloc(1, sizeof(bignum_t));
  b->d = (bignum_bit_t*) calloc(digits, sizeof(bignum_bit_t));
  b->alloced = digits;
  return b;
}

void bignum_destroy(bignum_t* b)
{
  if (b)
    free(b);
}

void bignum_set(bignum_t* b, int number)
{
  if (number < 0)
    b->neg = !!(number = -number); /* abs */
  while (number != 0)
  {
    b->d[b->digits++] = (number % 10);
    number /= 10;
  }
}

char* bignum_stringify(bignum_t* b)
{
  int i = 0;
  char* number = malloc(b->digits + 2); /* extra for sign and '\0' */
  if (b->neg)
  {
    number[0] = '-';
    ++i;
  }
  number[b->digits + i] = 0;
  for (; i < b->digits + b->neg; ++i)
    number[i] = b->d[b->digits - i - !b->neg] + '0';
  return number;
}

void bignum_negate(bignum_t* b)
{
  b->neg = !b->neg;
}

/* 1 - not equal, 0 - equal */
/*
int bignum_compare(bignum_t* a, bignum_t* b)
{
  return (a->digits != b->digits) ? 1 : memcmp(a->d, b->d, a->digits) ? 1 : 0;
}
*/

bignum_t* bignum_add(bignum_t* a, bignum_t* b)
{
  int i, max_digits = (a->digits > b->digits) ? a->digits : b->digits;
  bignum_t* result = bignum_reserve(max_digits + 1);
  result->digits = max_digits + 1; /* expect possible carry */

  bignum_bit_t ba, bb, bcarry = 0, sum;
  for (i = 0; i < result->digits; ++i)
  {
    ba = (i < a->digits) ? (a->neg ? -a->d[i] : a->d[i]) : 0;
    bb = (i < b->digits) ? (b->neg ? -b->d[i] : b->d[i]) : 0;
    sum = ba + bb + bcarry;
    bcarry = sum / 10;
    result->d[i] = sum % 10;
  }

  if (!result->d[result->digits - 1])
    result->digits--; /* no carry on last digit */

  return result;
}

bignum_t* bignum_substract(bignum_t* a, bignum_t* b)
{
  return NULL;
}


int main()
{
  bignum_t* a = bignum_create(94510);
  ppb(a);
  char* a_str = bignum_stringify(a);
  printf("number: %s alloced: %u, neg: %d, digits: %u\n", a_str, a->alloced, a->neg, a->digits);
  bignum_t* b = bignum_create(15509);
  ppb(b);
  bignum_t* result = bignum_add(a, b);
  char* b_str = bignum_stringify(b);
  char* r_str = bignum_stringify(result);
  ppb(result);
  printf("%s + %s = %s\n", a_str, b_str, r_str);
  free(a_str);
  free(b_str);
  free(r_str);
  bignum_destroy(b);
  bignum_destroy(result);
  bignum_destroy(a);
  return 0;
}
