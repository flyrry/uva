#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

typedef struct
{
  char c;
  int f;
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
  string line;
  int first = 1;

  while (getline(cin, line))
  {
    int i, sz;
    symbol freqs[256] = {0, 0};
    for (i = 0, sz = line.size(); i < sz; ++i)
    {
      freqs[line[i]].c = line[i];
      ++freqs[line[i]].f;
    }
    qsort(freqs, 256, sizeof(symbol), compare_symbols);

    if (!first) cout << endl;
    first = 0;

    for (i = 0; i < 256; ++i)
    {
      if (freqs[i].c)
        cout << (int)freqs[i].c << " " << (int)freqs[i].f << endl;
    }
  }
  return 0;
}
