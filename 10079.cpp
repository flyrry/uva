/*
 * Lazy caterer's sequence
 * p = n(n+1)/2 + 1
 */

#include <iostream>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  long long n;
  while (cin >> n) {
    if (n < 0) break;
    cout << n*(n+1)/2 + 1 << endl;
  }
  return 0;
}
