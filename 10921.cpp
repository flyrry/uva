#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  char c;
  while (cin.get(c)) {
    switch (c) {
      case 'A': case 'B': case 'C':
        c = '2'; break;
      case 'D': case 'E': case 'F':
        c = '3'; break;
      case 'G': case 'H': case 'I':
        c = '4'; break;
      case 'J': case 'K': case 'L':
        c = '5'; break;
      case 'M': case 'N': case 'O':
        c = '6'; break;
      case 'P': case 'Q': case 'R': case 'S':
        c = '7'; break;
      case 'T': case 'U': case 'V':
        c = '8'; break;
      case 'W': case 'X': case 'Y': case 'Z':
        c = '9'; break;
    }
    cout << c;
  }
  return 0;
}
