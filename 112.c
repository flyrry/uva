#include <stdio.h>
#include <stdlib.h>

typedef long long llong;

llong target, sum;  /* target number (we're looking for it) and current sum */
llong n;            /* last number (or part of it) read */
int p;              /* stack pointer */
int depth;          /* current depth level in the tree */
char c;             /* last character read from stdin */
short found;        /* did we find our target number in this tree? */
short leaf;         /* is it leaf? */
short sign;
char prev;

int main(void) {
  llong stack[10000]; /* stack to hold node numbers */
  for (;;) {
    scanf("%lld", &target);
    depth = 0;
    sum = n = 0;
    leaf = 0;
    prev = 'a';
    p = 1;
    sign = 1;
    found = 0;
    while ((c = getchar())) {
      if (c == EOF) return 0;
      if (c == '(') {
        if (depth > 0) {
          if (prev != ')') {
            sum += n;
            stack[p] = n;
            ++p;
            n = 0;
            sign = 1;
          }
        }
        ++depth;
      } else if (c == ')') {
        if (prev == '(') {
          ++leaf;
        } else {
          sum -= stack[--p];
          leaf = 0;
        }
        if (leaf == 2) {
          if (sum == target) found = 1;
          leaf = 0;
        }
        --depth;
        if (!depth) break;
      } else if (c == '-') {
        sign = -1;
      } else if (c >= '0' && c <= '9') {
        n = n * 10 + sign * (c - '0');
        leaf = 0;
      }

      if (c == '(' || c == ')' || (c >= '0' && c <= '9') || c == '-')
        prev = c;
    }
    if (found) printf("yes\n");
    else printf("no\n");
  }
  return 0;
}
