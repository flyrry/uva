/*
 * DP solution. Picking lowest number for each multiplier (2,3,5) that is higher than last ugly number.
 * Meanwhile keeping the index for each multiplier pointing at next ugly number to multiply.
 */
#include <stdio.h>
#include <stdlib.h>

typedef int ugly_t;
ugly_t ugly[1500];

#define MIN3(a, b, c) (((a) < ((b) < (c) ? (b) : (c))) ? (a) : ((b) < (c) ? (b) : (c)))

int main(void)
{
  ugly[0] = 1;
  int idx2, idx3, idx5;
  ugly_t n2, n3, n5;
  idx2 = idx3 = idx5 = 0;

  int i = 0;
  for (i = 1; i < 1500; ++i) {
    n2 = ugly[idx2] * 2;
    n3 = ugly[idx3] * 3;
    n5 = ugly[idx5] * 5;
    ugly_t m = MIN3(n2, n3, n5);
    if (n2 == m) {
      ++idx2;
      if (n2 == n3) ++idx3;
      if (n2 == n5) ++idx5;
    }
    else if (n3 == m) {
      ++idx3;
      if (n3 == n5) ++idx5;
    }
    else idx5++;
    ugly[i] = m;
  }

  printf("The 1500'th ugly number is %d.\n", ugly[1499]);

  return 0;
}

/*      0
 *      1 2 3 4 5 6
 * idx2       ^
 * idx3     ^
 * idx5   ^
 */
