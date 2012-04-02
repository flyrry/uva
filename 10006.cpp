#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

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

// exponentiation by squaring (with modulo part incorporated)
template<typename T> T es(T a, T n, T m)
{
  T am = a % m;
  if (n == 1) return am;
  if (n % 2)
    return am * es(am * am, (n - 1)/2, m) % m;
  return es(am * am, n/2, m);
}

int main()
{
  ios::sync_with_stdio(false);
  list<size_t> primes, carmichaels;
  sieve_of_eratosthenes(2 << 15, primes);
  size_t n;
  for (size_t i(3); i < 65000; ++i) {
    if (binary_search(primes.begin(), primes.end(), i))
      continue;
    size_t c(2);
    for (; c < i; ++c) {
      if (es(c, i, i) != c)
        break;
    }
    if (c == i)
      carmichaels.push_back(i);
  }

  while (cin >> n) {
    if (!n) break;
    if (binary_search(carmichaels.begin(), carmichaels.end(), n))
      cout << "The number " << n << " is a Carmichael number." << endl;
    else
      cout << n << " is normal." << endl;
  }
  return 0;
}
