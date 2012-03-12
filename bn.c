#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "bn.h"

int min(int a, int b);
int max(int a, int b);
bignum_t take_n(bignum_t x, int times);

bignum_t bignum_create(int number)
{
  return bignum_set(bignum_reserve(BIT_CHUNK_SIZE), number);
}

bignum_t bignum_create_from_string(const char* str)
{
  int has_sign = 0, i;
  size_t len = strlen(str);
  bignum_t b = bignum_reserve(len);
  b.neg = (str[0] == '-');
  if (b.neg || str[0] == '+')
    has_sign = 1;
  b.digits = len - has_sign;
  for (i = has_sign; i < len; ++i)
    b.d[len - i - 1] = str[i] - '0';
  return b;
}

bignum_t bignum_reserve(int digits)
{
  assert(digits > 0);
  bignum_t b;
  b.d = (bignum_bit_t*) calloc(digits, sizeof(bignum_bit_t));
  b.neg = b.digits = 0;
  b.alloced = digits;
  return b;
}

void bignum_destroy(bignum_t* b)
{
  if (b->alloced)
    free(b->d);
  b->d = NULL;
  b->alloced = b->neg = b->digits = 0;
}

void bignum_destroy_multiple(int n_args, ...)
{
  va_list ap;
  va_start(ap, n_args);
  while (n_args--)
  {
    bignum_t* b = va_arg(ap, bignum_t*);
    if (b->alloced)
      free(b->d);
    b->d = NULL;
    b->alloced = b->neg = b->digits = 0;
  }
  va_end(ap);
}

bignum_t bignum_set(bignum_t b, int number)
{
  if (number < 0)
    b.neg = !!(number = -number); /* abs */
  while (number)
  {
    b.d[b.digits++] = (number % 10);
    number /= 10;
  }
  if (!b.digits) /* number = 0 case */
    b.digits = 1;
  return b;
}

char* bignum_stringify(bignum_t b)
{
  int i = 0;
  char* number = malloc(b.digits + 2); /* extra for sign and '\0' */
  if (b.neg)
  {
    number[0] = '-';
    ++i;
  }
  number[b.digits + i] = 0;
  for (; i < b.digits + b.neg; ++i)
    number[i] = b.d[b.digits - i - !b.neg] + '0';
  return number;
}

bignum_t bignum_negate(bignum_t b)
{
  b.neg = !b.neg;
  return b;
}

/* -1 => a < b, 1 => a > b, 0 => equal */
int bignum_compare(bignum_t a, bignum_t b)
{
  int i;
  if (a.digits < b.digits)
    return (2*b.neg - 1);
  if (a.digits > b.digits)
    return (-2*a.neg + 1);
  for (i = a.digits - 1; i >= 0; --i)
  {
    if (a.d[i] < b.d[i])
      return -1;
    if (a.d[i] > b.d[i])
      return 1;
  }
  return 0;
}

bignum_t bignum_add(bignum_t a, bignum_t b)
{
  if (a.neg && !b.neg)
    return bignum_substract(b, bignum_negate(a));
  if (!a.neg && b.neg)
    return bignum_substract(a, bignum_negate(b));

  int i, max_digits = max(a.digits, b.digits);
  bignum_t result = bignum_reserve(max_digits + 1);
  result.digits = max_digits + 1; /* expect possible carry */

  bignum_bit_t ba, bb, bcarry = 0, sum;
  for (i = 0; i < result.digits; ++i)
  {
    ba = (i < a.digits) ? (a.neg ? -a.d[i] : a.d[i]) : 0;
    bb = (i < b.digits) ? (b.neg ? -b.d[i] : b.d[i]) : 0;
    sum = ba + bb + bcarry;
    bcarry = sum / 10;
    sum = (sum < 0) ? -sum : sum;
    result.d[i] = sum % 10;
  }

  while (!result.d[result.digits - 1] && (result.digits - 1)) /* trim trailing 0s */
    --result.digits;
  result.neg = (a.neg && b.neg);

  return result;
}

bignum_t bignum_substract(bignum_t a, bignum_t b)
{
  if (a.neg && b.neg)
    return bignum_substract(bignum_negate(b), a);
  if (a.neg && !b.neg)
    return bignum_negate(bignum_add(bignum_negate(a), b));
  if (!a.neg && b.neg)
    return bignum_add(a, bignum_negate(b));
  if (bignum_compare(a, b) == -1)
    return bignum_negate(bignum_substract(b, a));

  int i, max_digits = max(a.digits, b.digits);
  bignum_t result = bignum_reserve(max_digits + 1);
  result.digits = max_digits + 1; /* expect possible carry */

  bignum_bit_t ba, bb, bcarry = 0, diff;
  for (i = 0; i < result.digits; ++i)
  {
    ba = (i < a.digits) ? a.d[i] : 0;
    bb = (i < b.digits) ? b.d[i] : 0;
    diff = ba - bb - bcarry;
    bcarry = diff < 0;
    diff = (diff < 0) ? 10 + diff : diff;
    result.d[i] = diff;
  }

  while (!result.d[result.digits - 1] && (result.digits - 1)) /* trim trailing 0s */
    --result.digits;
  return result;
}

bignum_t bignum_copy(bignum_t b, size_t reserved_size)
{
  bignum_t result = bignum_reserve(max(b.digits, reserved_size));
  memcpy(result.d, b.d, sizeof(bignum_bit_t) * b.digits);
  result.neg = b.neg;
  result.digits = b.digits;
  return result;
}

bignum_t bignum_pad(bignum_t b, size_t length, bignum_bit_t digit)
{
  size_t i;
  bignum_t result = bignum_copy(b, length);
  for (i = result.digits; i < length; ++i)
    result.d[i] = digit;
  result.digits = i;
  return result;
}

bignum_t bignum_multiply(bignum_t x, bignum_t y)
{
  if (x.digits == 1)
    return take_n(y, x.d[0]);
  if (y.digits == 1)
    return take_n(x, y.d[0]);
  /* pad to equal length */
  bignum_t xp = bignum_pad(x, max(y.digits, x.digits), 0);
  bignum_t yp = bignum_pad(y, max(x.digits, y.digits), 0);
  bignum_t x1, x2, y1, y2;
  bignum_split(xp, &x2, &x1);
  bignum_split(yp, &y2, &y1);
  bignum_t a = bignum_multiply(x1, y1);
  bignum_t b = bignum_multiply(x2, y2);
  bignum_t s1 = bignum_add(x1, x2);
  bignum_t s2 = bignum_add(y1, y2);
  bignum_t c = bignum_multiply(s1, s2);
  bignum_t sab = bignum_add(a, b);
  bignum_t k = bignum_substract(c, sab);
  int shift_digits = min(x1.digits, x2.digits);
  bignum_t a_rebased = bignum_shift(a, 2 * shift_digits);
  bignum_t k_rebased = bignum_shift(k, shift_digits);
  bignum_t ak = bignum_add(a_rebased, k_rebased);
  bignum_t result = bignum_add(ak, b);
  bignum_destroy_multiple(16,
                          &x1, &x2, &y1, &y2,
                          &xp, &yp, &a, &b,
                          &s1, &s2, &c, &sab,
                          &k, &a_rebased, &k_rebased, &ak);
  result.neg = (x.neg ^ y.neg);
  return result;
}

/*
 * internal 
 */
int min(int a, int b)
{
  return (a < b) ? a : b;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

void bignum_split(bignum_t b, bignum_t* p1, bignum_t* p2)
{
  int i;
  if (b.digits < 2)
    return;
  *p1 = bignum_reserve(b.digits / 2);
  p1->digits = b.digits / 2;
  *p2 = bignum_reserve(b.digits - (b.digits / 2));
  p2->digits = b.digits - (b.digits / 2);
  for (i = 0; i < b.digits/2; ++i)
    p1->d[i] = b.d[i];
  for (; i < b.digits; ++i)
    p2->d[i - b.digits/2] = b.d[i];
}

bignum_t bignum_shift(bignum_t b, int times)
{
  int i;
  bignum_t result = bignum_reserve(b.digits + times);
  result.digits = b.digits + times;
  for (i = 0; i < times; ++i)
    result.d[i] = 0;
  for (; i < result.digits; ++i)
    result.d[i] = b.d[i - times];
  return result;
}

bignum_t take_n(bignum_t b, int times)
{
  int i;
  if (!times)
    return bignum_create(0);
  bignum_t result;
  bignum_t sum = bignum_create(0);
  for (i = 0; i < times; ++i)
  {
    result = bignum_add(sum, b);
    bignum_destroy(&sum);
    sum = result;
  }
  return result;
}
