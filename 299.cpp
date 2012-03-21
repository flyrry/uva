#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int cases, length;
  int carts[50];
  cin >> cases;
  while (cases--) {
    cin >> length;
    for (int i(0); i < length; ++i)
      cin >> carts[i];

    int swaps = 0;
    bool in_order;
    do {
      in_order = true;
      for (int i(0); i < length - 1; ++i) {
        if (carts[i] > carts[i+1]) {
          swap(carts[i], carts[i+1]);
          ++swaps;
          in_order = false;
        }
      }
    } while (!in_order);
    cout << "Optimal train swapping takes " << swaps << " swaps." << endl;
  }
  return 0;
}
