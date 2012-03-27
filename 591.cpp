#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t n, h, set = 0;
  vector<size_t> stacks;
  while (cin >> n) {
    if (!n) break;
    stacks.clear();
    for (size_t i(0); i < n; ++i) {
      cin >> h;
      stacks.push_back(h);
    }
    sort(stacks.begin(), stacks.end());
    size_t average = accumulate(stacks.begin(), stacks.end(), 0, plus<size_t>()) / n;
    vector<size_t>::iterator lb = lower_bound(stacks.begin(), stacks.end(), average, less_equal<size_t>());
    cout << "Set #" << ++set << endl << "The minimum number of moves is " << accumulate(lb, stacks.end(), 0, plus<size_t>()) - (stacks.end() - lb) * average << "." << endl << endl;
  }
  return 0;
}
