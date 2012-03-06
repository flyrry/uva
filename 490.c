#include <stdio.h>
#include <string.h>

int main()
{
  char text[100][100], c;
  int i = 0, k = 0, max = 0, last;
  memset(text, ' ', sizeof(char) * 100 * 100);
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      ++i;
      max = (k > max) ? k : max;
      k = 0;
    } else {
      text[i][k++] = c;
    }
  }
  last = --i;
  for (k = 0; k < max; ++k) {
    for (i = last; i >= 0; --i) {
      putchar(text[i][k]);
    }
    putchar('\n');
  }
  return 0;
}
