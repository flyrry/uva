#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

typedef list<int> numbers;

int main()
{
  ios::sync_with_stdio(false);
  size_t n, d;
  list<int> nums, sorted;
  while (cin >> n) {
    nums.clear();
    sorted.clear();
    size_t flips = 0;
    for (int i(0); i < n; ++i) {
      cin >> d;
      nums.push_back(d);
      sorted.push_back(d);
    }
    sorted.sort();
    for (int i(0); i < n; ++i) {
      numbers::iterator start = nums.begin();
      advance(start, i);
      numbers::iterator in(find(start, nums.end(), sorted.front()));
      flips += distance(nums.begin(), in) - i;
      nums.splice(start, nums, in);
      sorted.pop_front();
    }

    cout << "Minimum exchange operations : " << flips << endl;
  }
  return 0;
}
