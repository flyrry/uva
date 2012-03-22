#include <iostream>

using namespace std;

int main(void) {
  int n;
  long long fib[51];
  fib[0] = 1;
  fib[1] = 2;
  for (int i = 1; i < 50; ++i) {
    fib[i+1] = fib[i-1] + fib[i];
  }
  while (cin >> n) {
    if (!n) return 0;
    cout << fib[n-1] << endl;
  }
}
