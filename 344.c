#include <stdio.h>
#include <string.h>

enum { I = 0, V, X, L, C };

int main()
{
  int i;
  int romans[101][5];
  memset(romans, 0, sizeof(int) * 101 * 5);

  for (i = 1; i < 100; ++i)
  {
    int d1 = i / 10;
    int d2 = i % 10;

    if (d1 == 4)
    {
      romans[i][L] += 1;
      romans[i][X] += 1;
    }
    else if (d1 == 9)
    {
      romans[i][C] += 1;
      romans[i][X] += 1;
    }
    else
    {
      romans[i][L] += d1 / 5;
      romans[i][X] += d1 % 5;
    }

    if (d2 == 4)
    {
      romans[i][V] += 1;
      romans[i][I] += 1;
    }
    else if (d2 == 9)
    {
      romans[i][X] += 1;
      romans[i][I] += 1;
    }
    else
    {
      romans[i][V] += d2 / 5;
      romans[i][I] += d2 % 5;
    }

    int r;
    for (r = I; r <= C; ++r)
      romans[i][r] += romans[i-1][r];
  }

  romans[100][I] = romans[99][I];
  romans[100][V] = romans[99][V];
  romans[100][X] = romans[99][X];
  romans[100][L] = romans[99][L];
  romans[100][C] = romans[99][C] + 1;

  int number;
  while (scanf("%d", &number))
  {
    if (!number)
      break;
    printf("%d: %d i, %d v, %d x, %d l, %d c\n", number, romans[number][I], romans[number][V], romans[number][X], romans[number][L], romans[number][C]);
  }
  return 0;
}
