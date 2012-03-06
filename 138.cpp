/*
 * Arithmetic progression gives:
 * (m-1)m/2 = (n-m)(m+n+1)/2
 *        ==>
 * 2m^2 = n^2 + n
 *        ==>
 * m = sqrt((n^2+n)/2)
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  long long k, m, n = 8;
  for (int i = 0; i < 10; ++i) {
    for (;;++n) {
      k = (n%2) ? ((n+1)/2)*n : (n/2)*(n+1);
      m = sqrt(k);
      if (k == m * m) {
        cout << fixed << setprecision(0) << setw(10) << m << fixed << setprecision(0) << setw(10) << n << endl;
        ++n;
        break;
      }
    }
  }
  return 0;
}
