#include <iostream>
#include <string.h>

using namespace std;

/*
void ppnum(int num[9])
{
  for (int i = 0; i < 9; ++i)
    cout << num[i] << " ";
  cout << endl;
}
*/

int main(void)
{
  ios::sync_with_stdio(false);
  int a, b;
  int grades[] = {1,            // 0
                  10,           // 1
                  100,          // 2
                  1000,         // 3
                  10000,        // 4
                  100000,       // 5
                  1000000,      // 6
                  10000000,     // 7
                  100000000,    // 8
                  1000000000};  // 9
  int num_a[10];
  int num_b[10];
  while (true) {
    cin >> a >> b;
    if (!(a||b))
      return 0;

    memset(num_a, 0, sizeof(int) * 10);
    memset(num_b, 0, sizeof(int) * 10);

    for(int i = 1; i < 10; ++i) {
      // num_a[i] = ((9999 % 1000) - 99) / 100;
      //               ^
      // num_a[0] == 0
      num_a[i] = ((a % grades[i]) - num_a[i-1]) / grades[i-1];
      num_b[i] = ((b % grades[i]) - num_b[i-1]) / grades[i-1];
    }

    /*
    ppnum(num_a);
    ppnum(num_b);
    */

    // sum
    int carries = 0;
    for (int i = 0; i < 10; ++i)
    {
      int s = num_a[i] + num_b[i];
      if (s > 9) {
        ++carries;
        if (i < 9)
          num_a[i+1]++;
      }
    }

    if (!carries)
      cout << "No carry operation." << endl;
    else
    {
      if (carries % 10 == 1)
        cout << carries << " carry operation." << endl;
      else
        cout << carries << " carry operations." << endl;
    }
  }
}
