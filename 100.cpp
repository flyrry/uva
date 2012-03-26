#include <string>
#include <iostream>

using namespace std;

int count(size_t  n) {
  int c = 1;
  while (n != 1) {
    if (n % 2) n = 3 * n + 1;
    else n /= 2;
    ++c;
  }
  return c;
}

int main(void) {
  size_t i, j;
  while (cin >> i >> j) {
    size_t diff(0);
    for (size_t k = min(i, j); k <= max(i, j); ++k) {
      size_t n = count(k);
      if (n > diff) diff = n;
    }
    cout << i << " " << j << " " << diff << endl;
  }
  return 0;
}

