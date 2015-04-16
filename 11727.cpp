#include <iostream>

using namespace std;

inline void swapifless(unsigned& a, unsigned& b)
{
  if (a < b) {
    swap(a, b);
  }
}

int main(void)
{
  ios::sync_with_stdio(false);
  unsigned cases;
  unsigned s[3]; // salaries
  cin >> cases;
  for (unsigned i = 1; i <= cases; ++i) {
    cin >> s[0] >> s[1] >> s[2];
    
    // sorting network of #3
    swapifless(s[0], s[2]);
    swapifless(s[1], s[2]);
    swapifless(s[0], s[1]);

    cout << "Case " << i << ": " << s[1] << endl;
  }
  return 0;
}

