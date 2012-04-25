#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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

size_t n;

inline bool divides_evenly(size_t p) { return !(n % p); }

int main()
{
  ios::sync_with_stdio(false);
  vector<size_t> primes;
  sieve_of_eratosthenes(1000000, primes);
  while ((cin >> n) && n) cout << n << " : " << count_if(primes.begin(), primes.end(), divides_evenly) << endl;
  return 0;
}
