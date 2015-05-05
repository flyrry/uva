#include <iostream>
#include <string>
#include <map>

using namespace std;

namespace p10141 {
struct key_t {
  key_t(unsigned i, unsigned r, unsigned price) : i(i), r(r), price(price) {}
  bool operator<(const key_t& other) const
  {
    if (r != other.r)
      return r > other.r;
    if (price != other.price)
      return price < other.price;
    return i < other.i;
  }

  unsigned i, r;
  double price;
};
}

int main(void)
{
  unsigned n, p;
  unsigned rfp = 0;
  while (cin >> n >> p) {
    if (!(n|p)) break;
    
    string _discard;
    getline(cin, _discard);

    // skip requirements
    while (n--)
      getline(cin, _discard);

    map<p10141::key_t, string> proposals;
    for (unsigned i = 0; i < p; ++i) {
      string name;
      getline(cin, name);
      double price;
      unsigned r;
      cin >> price >> r;
      getline(cin, _discard);
      p10141::key_t key(i, r, price);
      proposals[key] = name;

      // skip met requirements
      while (r--)
        getline(cin, _discard);
    }

    if (rfp) cout << endl;
    cout << "RFP #" << ++rfp << endl;
    cout << proposals.begin()->second << endl;
  }
  return 0;
}
