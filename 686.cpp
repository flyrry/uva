#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>

using namespace std;

typedef list<size_t> list_t;

template<typename T> void sieve_of_eratosthenes(size_t upper_limit, T& container, bool include_one = false) {
  bool sieve[upper_limit + 1]; // input is inclusive range
  for (size_t i(0); i < upper_limit; ++i)
    sieve[i] = true;
  for (size_t i(2); i < sqrt(upper_limit); ++i) {
    if (!sieve[i]) continue;
    for(size_t n(i*i); n < upper_limit; n += i) {
      sieve[n] = false;
    }
  }
  // I wish there was a copy_if
  if (include_one) container.push_back(1);
  for (size_t i(2); i < upper_limit; ++i) {
    if (sieve[i]) container.push_back(i);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  size_t n;
  list_t primes;
  sieve_of_eratosthenes(2<<14, primes);
  while (cin >> n) {
    if (!n) break;
    list_t::iterator i(primes.begin());
    size_t pairs = 0;
    do {
      if (binary_search(primes.begin(), primes.end(), n - (*i))) {
        ++pairs;
      }
      ++i;
    } while (*i <= n/2);
    cout << pairs << endl;
  }
  return 0;
}
