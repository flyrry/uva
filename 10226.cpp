#include <iostream>
#include <map>
#include <iomanip>
#include <cstdlib>

using namespace std;

typedef map<string, size_t> frequencies;

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  string tree;
  frequencies species;
  getline(cin, tree); // not really a tree, just keeping I/O methods consistent
  cases = atoi(tree.c_str());
  getline(cin, tree); // skip initial newline
  bool first = true;
  while (cases--) {
    if (!first)
      cout << endl;
    first = false;

    species.clear();
    size_t total = 0;
    while (getline(cin, tree) && !tree.empty()) {
      ++species[tree];
      ++total;
    }

    for (frequencies::const_iterator s(species.begin()), end(species.end()); s != end; ++s)
      cout << s->first << " " << fixed << setprecision(4) << ((double)s->second / total * 100.0) << endl;
  }
  return 0;
}
