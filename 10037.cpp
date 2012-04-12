#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> hpair;

int main(void) {
  vector<int> left, right;
  vector<hpair> history;
  int cases;
  int j, k, n;
  int sum, man;

  cin >> cases;

  while (cases--) {
    cin >> n;
    sum = 0;
    left.clear();
    right.clear();
    history.clear();

    while (n--) {
      cin >> man;
      left.push_back(man);
    }

    sort(left.begin(), left.end());

    while (!left.empty()) {

      switch (left.size()) {
        case 1:	// last one
          sum += left.front();
          history.push_back(hpair(left.front(), -1));
          left.clear();
          break;
        case 2:	// last two
          sum += max(left[0], left[1]);
          history.push_back(hpair(min(left[0], left[1]), max(left[0], left[1])));
          left.clear();
          break;
        default:
          if (left[0] + left[left.size()-2] < 2 * left[1]) {
            j = left.back();
            left.pop_back();
            sum += j + left[0];
            right.push_back(j);
            history.push_back(hpair(left[0], j));
            history.push_back(hpair(left[0], -1));
          } else {
            j = left.back();
            left.pop_back();
            k = left.back();
            left.pop_back();
            right.push_back(j);
            right.push_back(k);
            if (left.size() == 1) {
              sum += left[0] + j + k;
              history.push_back(hpair(left[0], k));
              history.push_back(hpair(left[0], -1));
              history.push_back(hpair(left[0], j));
              left.clear();
            } else {
              sum += left[0] + j + 2 * left[1];
              history.push_back(hpair(left[0], left[1]));
              history.push_back(hpair(left[0], -1));
              history.push_back(hpair(min(j, k), max(j, k)));
              history.push_back(hpair(left[1], -1));
            }
          }
          break;
      }
    }
    cout << sum << endl;
    for (int i = 0; i < history.size(); ++i) {
      cout << history[i].first;
      if (history[i].second != -1) cout << " " << history[i].second;
      cout << endl;
    }
    if (cases) cout << endl;
  }
  return 0;
}

