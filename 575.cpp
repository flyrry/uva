#include <iostream>
#include <string>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  string skewed;
  size_t base[31];
  for (size_t i = 0; i < 31; ++i)
    base[i] = (1 << (i+1)) - 1;

  while (cin >> skewed) {
    size_t decimal = 0;
    size_t n = 0;
    for (int i = skewed.size() - 1; i >= 0; --i, ++n) {
      if (skewed[i] == '2')
        decimal += base[n] * 2;
      else if (skewed[i] == '1')
        decimal += base[n];
    }
    if (decimal)
      cout << decimal << endl;
    else return 0;
  }
  return 0;
}
