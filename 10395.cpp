#include <iostream>
#include <string>
#include <vector>
using namespace std;

void permute (string *s, int a, int b) {
  char c,d;

  c = (*s)[a-1];
  d = (*s)[b-1];
  (*s)[a-1] = d;
  (*s)[b-1] = c;

  cout << *s << endl;
}

void do_stuff (string *a, int n) {
  if (n == 3) {
    permute (a, 1, 2);
    permute (a, 1, 3);
    permute (a, 1, 2);
    permute (a, 1, 3);
    permute (a, 1, 2);
  } else {
    for (int i = 1; i < n; i++) {
      do_stuff (a, n-1);
      permute (a, i, n);
    }
  }
}

int main (void) {
  string input;

  // ugc
  // guc
  // cug
  // ucg
  // gcu
  // cgu
  //
  // 1  gucroth
  // 2  ugcroth
  // 3  cguroth
  // 4  gcuroth
  // 5  ucgroth
  // 6  cugroth
  // 7  rugcoth
  // 8  urgcoth
  // 9  grucoth
  // 10 rgucoth
  // 11 ugrcoth
  
  char a,b;

  while (cin >> input) {
    if (input.size() == 1) {
      cout << input << endl;
      continue;
    }

    if (input.size() == 2) {
      cout << input << endl;
      reverse(input.begin(), input.end());
      cout << input << endl;
      continue;
    }


    //permute (&input, 1, input.size());
    do_stuff (&input, input.size());
  }

  return 0;
}
