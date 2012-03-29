#include <stdio.h>
#include "bn.h" /* included for brevity, see bn.h bn.c for bignum code */

#define BUFF_SIZE 1024 * 1024

int main(void)
{
  bignum_t fib[5001];
  fib[0] = bignum_create(0);
  fib[1] = bignum_create(1);
  char out[BUFF_SIZE];
  setvbuf(stdout, out, _IOFBF, BUFF_SIZE * sizeof(char));
  size_t i, n;
  for (i = 2; i < 5001; ++i)
    fib[i] = bignum_add(fib[i-1], fib[i-2]);
  while (scanf("%d", &n) != EOF) {
    char* str = bignum_stringify(fib[n]);
    printf("The Fibonacci number for %d is %s\n", n, str);
  }
  return 0;
}
