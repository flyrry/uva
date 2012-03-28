#include <iostream>
#include <numeric>
#include <list>
#include <cstring>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  size_t cal[3651];
  while (cases--) {
    memset(cal, 0, sizeof(size_t) * 3651);
    size_t days, parties;
    cin >> days;
    cin >> parties;
    list<size_t> party_hs;
    while (parties--) {
      size_t h;
      cin >> h;
      if (h)
        party_hs.push_back(h);
    }

    for (size_t h = party_hs.back(); !party_hs.empty(); party_hs.pop_back()) {
      h = party_hs.back();
      for (size_t i = h - 1; i < days; i += h) {
        cal[i] = 1;
      }
    }

    for (size_t i = 5; i < days; i += 7) {
      cal[i] = 0;
      if (i + 1 < days)
        cal[i+1] = 0;
    }

    cout << accumulate(cal, cal + days, 0, plus<size_t>()) << endl;
  }
  return 0;
}
