#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t n, k;
  while (cin >> n >> k) {
    if (!n && !k)
      break;

    k = (k < (n-k)) ? n-k : k;

    list<size_t> dividend, divisor;

    for (size_t i(n); i > k; --i)
      dividend.push_back(i);
    for (size_t i(n-k); i > 1; --i)
      divisor.push_back(i);

    for (list<size_t>::iterator i(dividend.begin()), end(dividend.end()); i != end; ++i) {
      for (list<size_t>::iterator e(divisor.begin()), eend(divisor.end()); e != eend; ++e) {
        if (!(*i%*e))
        {
          *i /= *e;
          divisor.erase(e);
          break;
        }
      }
    }

    cout << accumulate(dividend.begin(), dividend.end(), 1LL, multiplies<long long>())/accumulate(divisor.begin(), divisor.end(), 1LL, multiplies<long long>()) << endl;
  }
  return 0;
}
