#include <iostream>
#include <string>
#include <stack>

using namespace std;

int n, w, m;
string l, r;
stack<int> wd;

int main(void) {
  while (cin >> n && n > 0) {
    m = 0;
    while (n--) {
      cin >> l;
      w = l.size();
      if (l.size() < 25) {
        cin >> r;
        w += r.size();
      }
      if (w > m) m = w;
      wd.push(w);
    }
    w = 0;
    while (!wd.empty()) {
      w += m - wd.top();
      wd.pop();
    }
    cout << w << endl;
  }
}
