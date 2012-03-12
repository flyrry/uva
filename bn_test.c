#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bn.h"

/*
 * remove for lib version
 */
void ppb(bignum_t b)
{
  int i;
  if (b.neg)
    printf("-");
  for (i = b.digits - 1; i >= 0; --i)
    printf("%d", b.d[i]);
  printf(" [negative: %d, digits: %d, alloced: %d]\n", b.neg, b.digits, b.alloced);
}
/*
 * remove for lib version
 */

int main()
{
  bignum_t a = bignum_create(-15500);
  printf("negative a: ");
  ppb(a);
  bignum_t b = bignum_create(94510);
  printf("positive b: ");
  ppb(b);
  bignum_t result = bignum_add(a, b);
  printf("a + b = ");
  ppb(result);
  printf("a ~ b = %d\n", bignum_compare(a,b));
  printf("b ~ a = %d\n", bignum_compare(b,a));
  printf("a ~ a = %d\n", bignum_compare(a,a));
  bignum_t diff = bignum_substract(a, b);
  printf("a - b = ");
  ppb(diff);
  bignum_t head, tail;
  bignum_split(a, &tail, &head);
  printf("head of a: ");
  ppb(head);
  printf("tail of a: ");
  ppb(tail);
  bignum_t s100 = bignum_shift(head, 2);
  printf("head * 100 = ");
  ppb(s100);
  bignum_t s10 = bignum_shift(tail, 1);
  printf("tail * 10 = ");
  ppb(s10);
  const char* x_str = "123456789012345678901234567890";
  const char* y_str = "-33333333333333333333333333333333333333333333333";
  bignum_t x = bignum_create_from_string(x_str);
  bignum_t y = bignum_create_from_string(y_str);
  printf("%s as bignum: ", x_str);
  ppb(x);
  printf("%s as bignum: ", y_str);
  ppb(y);
  bignum_t product = bignum_multiply(x, y);
  printf("a * b = ");
  ppb(product);
  const char* extra_long_x = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
  const char* extra_long_y = "36360291795869936842385267079543319118023385026001623040346035832580600191583895484198508262979388783308179702534403855752855931517013066142992430916562025780021771247847643450125342836565813209972590371590152578728008385990139795377610001";
  bignum_t e_x = bignum_create_from_string(extra_long_x);
  printf("extra long x: %s as bignum: ", extra_long_x);
  ppb(e_x);
  bignum_t e_y = bignum_create_from_string(extra_long_y);
  printf("extra long y: %s as bignum: ", extra_long_y);
  ppb(e_y);
  bignum_t long_product = bignum_multiply(e_x, e_y);
  printf("long product: ");
  ppb(long_product);
  const char* correct_lp = "363602917958699368423852670795433191180233850260016230403460358325806001915838954841985082629793887833081797025344038557528559315170130661429924309165620257800217712478476434501253428365658132099725903715901525787280083859901397953776100010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
  char* lp_str = bignum_stringify(long_product);
  printf("long product is %s\n", (!strcmp(lp_str, correct_lp)) ? "correct" : "NOT correct");
  free(lp_str);
  bignum_t n = bignum_create(-145);
  bignum_t d = bignum_create(144);
  printf("-145 / 144 = ");
  bignum_t q = bignum_divide(n, d);
  ppb(q);

  bignum_destroy(&a);
  bignum_destroy(&b);
  bignum_destroy(&result);
  bignum_destroy(&diff);
  bignum_destroy(&head);
  bignum_destroy(&tail);
  bignum_destroy(&s100);
  bignum_destroy(&s10);
  bignum_destroy(&x);
  bignum_destroy(&y);
  bignum_destroy(&product);
  bignum_destroy(&e_x);
  bignum_destroy(&e_y);
  bignum_destroy(&long_product);
  bignum_destroy(&n);
  bignum_destroy(&d);
  bignum_destroy(&q);
  return 0;
}

