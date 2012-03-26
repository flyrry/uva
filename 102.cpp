#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void) {
  size_t b1, g1, c1, b2, g2, c2, b3, g3, c3;

  while (cin >> b1 >> g1 >> c1 >> b2 >> g2 >> c2 >> b3 >> g3 >> c3) {
    string code = "GCB";
    size_t moves = g2 + g3 + c1 + c3 + b1 + b2;

    size_t n = g2 + g3 + b1 + b3 + c1 + c2;
    if (n <= moves) {
      moves = n;
      code = "GBC";
    }
    n = c2 + c3 + g1 + g3 + b1 + b2;
    if (n <= moves) {
      moves = n;
      code = "CGB";
    }
    n = c2 + c3 + b1 + b3 + g1 + g2;
    if (n <= moves) {
      moves = n;
      code = "CBG";
    }
    n = b2 + b3 + g1 + g3 + c1 + c2;
    if (n <= moves) {
      moves = n;
      code = "BGC";
    }
    n = b2 + b3 + c1 + c3 + g1 + g2;
    if (n <= moves) {
      moves = n;
      code = "BCG";
    }
    cout << code << " " << moves << endl;
  }
}

