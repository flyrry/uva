#include <stdio.h>

int main(void)
{
  int d;
  while (scanf("%d", &d) != EOF) {
    int i, first, second;
    int n = d;
    for (i = 1; i < n; ++i)
      n -= i;
    if (i % 2) {
      second = n;
      first = i + 1 - n;
    }
    else {
      second = i + 1 - n;
      first = n;
    }
    printf("TERM %d IS %d/%d\n", d, first, second);
  }
  return 0;
}
