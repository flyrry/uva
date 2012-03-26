#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

int p;
long temp;
long n;
long nums[10000];

int main(void) {
  while (cin >> n) {
    nums[p] = n;
    for (int i = p; i > 0; --i) {
      if (nums[i] < nums[i-1]) {
        swap(nums[i-1], nums[i]);
      } else break;
    }
    ++p;
    if (p % 2) {
      cout << nums[(int)trunc(p/2)] << endl;
    } else {
      cout << (int)trunc((nums[p/2-1] + nums[p/2])/2) << endl;
    }
  }
}
