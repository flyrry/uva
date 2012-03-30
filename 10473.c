#include <stdio.h>

int valueof(char c) {
  switch (c) {
    case 'F': case 'f': return 15;
    case 'E': case 'e': return 14;
    case 'D': case 'd': return 13;
    case 'C': case 'c': return 12;
    case 'B': case 'b': return 11;
    case 'A': case 'a': return 10;
    default: return (c - '0');
  }
}

int main(void)
{
  char c;
  int hex = 0, number = 0, start = 1;
  while ((c = getchar()) != EOF) {
    if (c == '-') break;
    if (c == '0' && start) continue;
    else start = 0;
    if (c == 'x') { hex = 1; continue; }
    if (c == '\n') {
      if (hex)
        printf("%d\n", number);
      else
        printf("0x%X\n", number);
      hex = number = 0;
      start = 1;
      continue;
    } else {
      if (hex)
        number = number * 16 + valueof(c);
      else
        number = number * 10 + (c - '0');
    }
  }
  return 0;
}
