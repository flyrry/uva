#include <stdio.h>
#include <stdlib.h>

int cases,n;
int a,b,c,j;

char *res;

int main(void) {
  res = malloc(sizeof(char) * 1000002);
  scanf("%d", &cases);

  while (cases--) {
    scanf("%d", &n);
    for (j = 1; j <= n; ++j) {
      scanf("%d %d", &a, &b);
      res[j] = a+b;
    }

    c = 0;
    for (; j > 0; j--) {
      res[j] += c;
      c = (res[j] > 9);
      if (c) res[j] -= 10;
    }

    if (c) res[0] = 1;
    else res[0] = 0;

    if (res[0]) putchar('1');
    for (j = 1; j <= n; ++j)
      putchar(res[j]+'0');

    putchar('\n');
    if (cases) putchar('\n');
  }

  free(res);
  return 0;
}
