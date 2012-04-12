#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int n;
  while (cin >> n) {
    if (n < 0) break;
    if (!n) { cout << 0 << endl; continue; }

    int power = 387420489; // starting power of 3 (3**18) that is less than 1000000001
    bool begin_output = false;
    do {
      int remainder = n % power;
      if (n - remainder) begin_output = true;
      if (begin_output)
        cout << (n - remainder) / power;
      n = remainder;
      power /= 3;
    } while (power);
    cout << endl;
  }
  return 0;
}
