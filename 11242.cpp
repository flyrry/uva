#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main(void) {
  int f,r,t;
  vector<double> front;
  vector<double> rear;
  vector<double> ratios;

  while (true) {
    front.clear();
    rear.clear();
    ratios.clear();

    cin >> f;
    if(f==0) return 0;
    cin >> r;
    while (f--) {
      cin >> t;
      front.push_back(t);
    }

    while (r--) {
      cin >> t;
      rear.push_back(t);
    }

    for (int i = 0; i < rear.size(); ++i) {
      for (int k = 0; k < front.size(); ++k) {
        ratios.push_back(rear[i]/front[k]);
      }
    }

    sort(ratios.begin(), ratios.end());

    double maxs = -1;
    double spread;
    for (int i = 0; i < ratios.size() - 1; ++i) {
      spread = ratios[i+1]/ratios[i];
      if (spread > maxs) maxs = spread;
    }

    cout << fixed << setprecision(2) << maxs << endl;
  }
}
