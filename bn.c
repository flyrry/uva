#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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

void bignum_destroy_multiple(int n_args, ...)
{
  va_list ap;
  va_start(ap, n_args);
  int i;
  for (i = 0; i < n_args; ++i)
  {
    bignum_t* b = va_arg(ap, bignum_t*);
    if (b)
      free(b);
  }
  va_end(ap);
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
  if (!b->digits) /* number = 0 case */
    b->digits = 1;
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
  for (i = a->digits - 1; i >= 0; --i)
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
    return bignum_substract(a, bignum_negate(bignum_copy_s(b)));

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

  while (!result->d[result->digits - 1] && (result->digits - 1)) /* trim trailing 0s */
    --result->digits;
  result->neg = (a->neg && b->neg);

  return result;
}

bignum_t* bignum_substract(bignum_t* a, bignum_t* b)
{
  /* shallow copy arguments before negating to leave them unaffected */
  /*
  if (a->neg && b->neg)
    return bignum_substract(bignum_copy_s(bignum_negate(b)), a);
  if (a->neg && !b->neg)
    return bignum_negate(bignum_add(bignum_copy_s(bignum_negate(a)), b));
  if (!a->neg && b->neg)
    return bignum_add(a, bignum_copy_s(bignum_negate(b)));
  if (bignum_compare(a, b) == -1)
    return bignum_negate(bignum_substract(b, a));
  */
  if (a->neg && b->neg)
    return bignum_substract(bignum_negate(bignum_copy_s(b)), a);
  if (a->neg && !b->neg)
    return bignum_negate(bignum_add(bignum_negate(bignum_copy_s(a)), b));
  if (!a->neg && b->neg)
    return bignum_add(a, bignum_negate(bignum_copy_s(b)));
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

  while (!result->d[result->digits - 1] && (result->digits - 1)) /* trim trailing 0s */
    --result->digits;
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

bignum_t* bignum_shift(bignum_t* b, int times)
{
  int i;
  bignum_t* result = bignum_reserve(b->digits + times);
  result->digits = b->digits + times;
  for (i = 0; i < times; ++i)
    result->d[i] = 0;
  for (; i < result->digits; ++i)
    result->d[i] = b->d[i - times];
  return result;
}

bignum_t* bignum_pad(bignum_t* b, int n, int digit)
{
  int i;
  bignum_t* padded = bignum_reserve(b->digits + n);
  padded->neg = b->neg;
  for (i = 0; i < b->digits; ++i)
    padded->d[i] = b->d[i];
  for (; i < n + b->digits; ++i)
    padded->d[i] = digit;
  padded->digits = i;
  return padded;
}

bignum_t* take_n(bignum_t* b, int times)
{
  int i;
  bignum_t* result = NULL;
  if (!times)
    return bignum_create(0);
  bignum_t* sum = bignum_create(0);
  for (i = 0; i < times; ++i)
  {
    result = bignum_add(sum, b);
    bignum_destroy(sum);
    sum = result;
  }
  return result;
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

bignum_t* bignum_multiply(bignum_t* x, bignum_t* y)
{
  bignum_t* x1, *x2, *y1, *y2;
  if (x->digits == 1)
    return take_n(y, x->d[0]);
  if (y->digits == 1)
    return take_n(x, y->d[0]);
  /*
  printf("x: ");
  ppb(x);
  printf("y: ");
  ppb(y);
  */
  /* pad to equal length */
  /*
  printf("padding by %d\n", x->digits - y->digits);
  */
  bignum_t* xp = bignum_pad(x, y->digits - x->digits, 0);
  bignum_t* yp = bignum_pad(y, x->digits - y->digits, 0);
  bignum_split(xp, &x2, &x1);
  bignum_split(yp, &y2, &y1);
  /*
  bignum_split(x, &x2, &x1);
  bignum_split(y, &y2, &y1);
  */
  /*
  printf("x1: "); ppb(x1);
  printf("x2: "); ppb(x2);
  printf("y1: "); ppb(y1);
  printf("y2: "); ppb(y2);
  */
  bignum_t* a = bignum_multiply(x1, y1);
  /*
  printf("a: "); ppb(a);
  */
  bignum_t* b = bignum_multiply(x2, y2);
  /*
  printf("b: "); ppb(b);
  */
  bignum_t* s1 = bignum_add(x1, x2);
  bignum_t* s2 = bignum_add(y1, y2);
  bignum_t* c = bignum_multiply(s1, s2);
  /*
  printf("c: "); ppb(c);
  */
  bignum_t* sab = bignum_add(a, b);
  /*
  printf("a+b: "); ppb(sab);
  */
  bignum_t* k = bignum_substract(c, sab);
  /*
  printf("k: "); ppb(k);
  */
  /*
  int shift_digits = min(max(x1->digits, x2->digits), max(y1->digits, y2->digits));
  */
  int shift_digits = min(x1->digits, x2->digits);
  /*
  printf("shifting by %d and %d\n", shift_digits*2, shift_digits);
  */
  bignum_t* a_rebased = bignum_shift(a, 2 * shift_digits);
  bignum_t* k_rebased = bignum_shift(k, shift_digits);
  bignum_t* ak = bignum_add(a_rebased, k_rebased);
  bignum_t* result = bignum_add(ak, b);
  /*
  printf("result: ");
  ppb(result);
  */
  /*bignum_destroy_multiple(16, x1, x2, y1, y2, a, b, s1, s2, c, sab, k, _100, _10, a100, k10, ak);*/
  printf("%d %d\n", x->neg, y->neg);
  result->neg = (x->neg ^ y->neg);
  return result;
}

int main()
{
  /* -15500, -155 */
  bignum_t* a = bignum_create(-15500);
  printf("a:");
  ppb(a);
  /* 94510 */
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
  ppb(a);
  ppb(b);
  bignum_t* first, *second;
  bignum_split(a, &first, &second);
  printf("first half: ");
  ppb(first);
  printf("second half: ");
  ppb(second);
  printf("* 100 = ");
  ppb(bignum_shift(first, 2));
  printf("* 10 = ");
  ppb(bignum_shift(second, 1));
  printf("a * b = ");
  bignum_t* x = bignum_create(-1234);
  bignum_t* y = bignum_create(5678);
  bignum_t* product = bignum_multiply(a, b);
  ppb(product);
  return 0;
}
