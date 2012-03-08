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
  printf(" [negative: %d, digits: %d, alloced: %d]\n", b->neg, b->digits, b->alloced);
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

/* shallow copy */
bignum_t* bignum_copy_s(bignum_t* b)
{
  bignum_t* copy = (bignum_t*) calloc(1, sizeof(bignum_t));
  copy->d = b->d;
  copy->digits = b->digits;
  copy->neg = b->neg;
  copy->alloced = b->alloced;
  return copy;
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

bignum_t* bignum_negate(bignum_t* b)
{
  b->neg = !b->neg;
  return b;
}

/* 1 - not equal, 0 - equal */
int bignum_compare(bignum_t* a, bignum_t* b)
{
  int i;
  if (a->digits < b->digits)
    return (2*b->neg - 1);
  if (a->digits > b->digits)
    return (-2*a->neg + 1);
  for (i = a->digits - 1; i >= 0; ++i)
  {
    if (a->d[i] < b->d[i])
      return -1;
    if (a->d[i] > b->d[i])
      return 1;
  }
  return 0;
}

bignum_t* bignum_add(bignum_t* a, bignum_t* b)
{
  /* shallow copy arguments before negating to leave them unaffected */
  if (a->neg && !b->neg)
    return bignum_substract(b, bignum_negate(bignum_copy_s(a)));
  if (!a->neg && b->neg)
    return bignum_substract(a, bignum_copy_s(bignum_negate(b)));

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
    sum = (sum < 0) ? -sum : sum;
    result->d[i] = sum % 10;
  }

  if (!result->d[result->digits - 1])
    result->digits--; /* no carry on last digit */
  result->neg = (a->neg && b->neg);

  return result;
}

bignum_t* bignum_substract(bignum_t* a, bignum_t* b)
{
  /* shallow copy arguments before negating to leave them unaffected */
  if (a->neg && b->neg)
    return bignum_substract(bignum_copy_s(bignum_negate(b)), a);
  if (a->neg && !b->neg)
    return bignum_negate(bignum_add(bignum_copy_s(bignum_negate(a)), b));
  if (!a->neg && b->neg)
    return bignum_add(a, bignum_copy_s(bignum_negate(b)));
  if (bignum_compare(a, b) == -1)
    return bignum_negate(bignum_substract(b, a));

  int i, max_digits = (a->digits > b->digits) ? a->digits : b->digits;
  bignum_t* result = bignum_reserve(max_digits + 1);
  result->digits = max_digits + 1; /* expect possible carry */

  bignum_bit_t ba, bb, bcarry = 0, diff;
  for (i = 0; i < result->digits; ++i)
  {
    ba = (i < a->digits) ? a->d[i] : 0;
    bb = (i < b->digits) ? b->d[i] : 0;
    diff = ba - bb - bcarry;
    bcarry = diff < 0;
    diff = (diff < 0) ? 10 + diff : diff;
    result->d[i] = diff;
  }

  if (!result->d[result->digits - 1])
    result->digits--;
  return result;
}

void bignum_split(bignum_t* b, bignum_t** p1, bignum_t** p2)
{
  int i;
  if (b->digits < 2)
  {
    p1 = p2 = NULL;
    return;
  }
  *p1 = bignum_reserve(b->digits / 2);
  (*p1)->digits = b->digits / 2;
  *p2 = bignum_reserve(b->digits - (b->digits / 2));
  (*p2)->digits = b->digits - (b->digits / 2);
  for (i = 0; i < b->digits/2; ++i)
    (*p1)->d[i] = b->d[i];
  for (; i < b->digits; ++i)
    (*p2)->d[i - b->digits/2] = b->d[i];
}

bignum_t* bignum_multiply(bignum_t* x, bignum_t* y)
{
  bignum_t* x1, *x2, *y1, *y2;
  bignum_split(a, a1, a2);
}

int main()
{
  bignum_t* a = bignum_create(-15509);
  printf("a:");
  ppb(a);
  bignum_t* b = bignum_create(94510);
  printf("b:");
  ppb(b);
  bignum_t* result = bignum_add(a, b);
  printf("a + b = ");
  ppb(result);
  printf("a ~ b = %d\n", bignum_compare(a,b));
  bignum_t* diff = bignum_substract(a, b);
  printf("a - b = ");
  ppb(diff);
  bignum_t* first, *second;
  bignum_split(b, &first, &second);
  ppb(first);
  ppb(second);
  return 0;
}
