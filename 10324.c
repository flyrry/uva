#include <stdio.h>

#define MAX_LENGTH 1000001
char line[MAX_LENGTH];
int id[MAX_LENGTH];

int main(void)
{
  int queries, q, i, j, c = 1;
  for (; scanf("%s\n", line) != EOF; ++c) {
    printf("Case %d:\n", c);
    id[0] = 0;
    for (q = 1; q < MAX_LENGTH; ++q) {
      if (line[q] != line[q-1]) id[q] = id[q-1] + 1;
      else id[q] = id[q-1];
    }

    scanf("%d\n", &queries);
    for (q = 0; q < queries; ++q) {
      scanf("%d %d\n", &i, &j);
      if (j < i) i ^= j ^= i ^= j;
      printf(id[i] == id[j] ? "Yes\n" : "No\n");
    }
  }
  return 0;
}
