/*
 * N! / (N-M)! / M!
 * 5 <= M <= N <= 100
 * this is a formula for binomial coefficient
 * 
 * using another (multiplicative) formula
 *  M
 *  _
 * | | (N-M+i)/i
 * i=1
 */

#include <iostream>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  double n,m;
  cout.precision(0);
  while (cin >> n >> m) {
    if (!n&&!m) break;
    double product = 1;
    for (int i = 1; i <= m; ++i)
      product *= (n-m+i)/i;

    cout << fixed << n << " things taken " << m << " at a time is " << product << " exactly." << endl;
  }
  return 0;
}
