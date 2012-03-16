#include <iostream>
#include <list>
#include <limits.h>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);

  int people, budget, hotels, weeks;
  while (cin >> people >> budget >> hotels >> weeks) {
    int minimum_sum = INT_MAX;
    int price, sum = INT_MAX;
    for (int h = 0; h < hotels; ++h) {
      cin >> price;
      for (int w = 0; w < weeks; ++w) {
        size_t beds;
        cin >> beds;
        if (beds < people)
          continue;
        sum = people * price;
        if (sum > budget)
          continue;
        minimum_sum = min(minimum_sum, sum);
      }
    }
    if (minimum_sum < INT_MAX)
      cout << minimum_sum << endl;
    else
      cout << "stay home" << endl;
  }
  return 0;
}
