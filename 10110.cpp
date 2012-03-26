#include <iostream>
#include <math.h>

using namespace std;

int main(void) {
  size_t n;
  while (cin >> n) {
    if (!n) return 0;
    size_t m = (int)sqrt(n);
    if (n == m*m) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
