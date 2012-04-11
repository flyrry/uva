#include <stdio.h>
#include <string.h>

typedef struct
{
  char c;
  size_t f;
} symbol;

int compare_symbols(const void* lhs, const void* rhs)
{
  const symbol* ls = (const symbol*) lhs;
  const symbol* rs = (const symbol*) rhs;
  if (ls->f == rs->f)
    return (rs->c - ls->c);
  return (ls->f - rs->f);
}

int main(void)
{
  /*
   * problem statement says maximum line length is 1000 characters
   * yet test cases seem to include lines with several \r's at the end
   * and also expect \r count in the output
   */
  char line[2000];
  int first = 1;
  while (fgets(line, 2000, stdin))
  {
    int i, sz;
    symbol freqs[256] = {0, 0};
    for (i = 0, sz = strcspn(line, "\n"); i < sz; ++i)
    {
      freqs[line[i]].c = line[i];
      ++freqs[line[i]].f;
    }
    qsort(freqs, 256, sizeof(symbol), compare_symbols);

    if (!first) printf("\n");
    first = 0;

    for (i = 0; i < 256; ++i)
    {
      if (freqs[i].c)
        printf("%d %d\n", freqs[i].c, freqs[i].f);
    }
  }
  return 0;
}
