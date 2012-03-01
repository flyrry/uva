#include <iostream>

using namespace std;

// exponentiation by squaring (with modulo part incorporated)
inline long long es(long long b, long long p, long long m)
{
  long long bm = b%m;
  if (p == 1) return bm;
  if (p % 2)
    return bm * es(bm*bm, (p-1)/2, m)%m;
  return es(bm*bm, p/2, m);
}

int main(void)
{
  ios::sync_with_stdio(false);

  long long b,p,m;
  while (cin >> b >> p >> m) {
    if (m == 1) {
      cout << "0" << endl;
      continue;
    }
    if (p == 0) {
      cout << "1" << endl;
      continue;
    }
    cout << es(b,p,m)%m << endl;
  }
  return 0;
}
