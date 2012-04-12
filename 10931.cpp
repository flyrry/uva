#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int n;
  while (cin >> n) {
    if (!n) break;

    int parity = 0;
    string bits;
    cout << "The parity of ";
    do {
      int on = (0x1 & n);
      bits.insert(0, 1, on ? '1' : '0');
      parity += on;
      n >>= 1;
    } while (n);
    cout << bits << " is " << parity << " (mod 2)." << endl;
  }
  return 0;
}
