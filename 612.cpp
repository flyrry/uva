#include <cstdio>
#include <list>

using namespace std;

typedef pair<size_t, size_t> attributes; // pair of "unsortedness" and "index" in the original chains array

bool attribute_compare(const attributes& lhs, const attributes& rhs) {
  if (lhs.first == rhs.first)
    return lhs.second < rhs.second; // maintain original order
  return lhs.first < rhs.first;
}

int main()
{
  size_t cases;
  char chains[100][51]; // 100 string of length 50 (plus trailing '\0')
  list<attributes> sortables;
  bool first = true;
  scanf("%d", &cases);
  while (cases--) {
    int sz, n;
    sortables.clear();

    if (!first)
      printf("\n");
    first = false;

    scanf("%d %d", &sz, &n);
    for (int i(0); i < n; ++i)
      scanf("%s", chains[i]);

    for (int i(0); i < n; ++i) {
      // two walks along each chain
      // first compute frequencies
      size_t As, Ts, Cs, Gs;
      As = Ts = Cs = Gs = 0;
      for (int k(0); k < sz; ++k) {
        if (chains[i][k] == 'A') ++As;
        else if (chains[i][k] == 'T') ++Ts;
        else if (chains[i][k] == 'C') ++Cs;
        else if (chains[i][k] == 'G') ++Gs;
      }
      // now walk and remove passed acid bases
      // from frequencies
      size_t unsortedness = 0;
      for (int k(0); k < sz; ++k) {
        if (chains[i][k] == 'A') --As;
        else if (chains[i][k] == 'T') { unsortedness += As + Cs + Gs; --Ts; }
        else if (chains[i][k] == 'C') { unsortedness += As; --Cs; }
        else if (chains[i][k] == 'G') { unsortedness += As + Cs; --Gs; }
      }
      // store for sorting
      sortables.push_back(make_pair(unsortedness, i));
    }

    sortables.sort(attribute_compare);

    for (list<attributes>::const_iterator i(sortables.begin()), end(sortables.end()); i != end; ++i)
      printf("%s\n", chains[i->second]);
  }
  return 0;
}
