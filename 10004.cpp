#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
  int n;
  int c;
  vector<int> nb;
  node() : n(-1), c(-1) {}
};

map<int,node> g;

bool mark(node& n, int c) {
  if (n.c == c) return true; // visited & all ok
  if (n.c == -1) {
    n.c = c;
    for (vector<int>::iterator i(n.nb.begin()), end(n.nb.end()); i != end; ++i) {
      if (!mark(g[*i], !c)) return false;
    }
    return true;
  }
  return false; // color mismatch
}

int main(void) {
  int n, l;
  while (true) {
    cin >> n;
    if (!n) return 0;
    cin >> l;
    int s;
    while (l--) {
      int a, b;
      cin >> a >> b;
      g[a].nb.push_back(b);
      g[b].nb.push_back(a);
      s = a;
    }
    bool possible = mark(g[s], 1);
    g.clear();
    if (possible) cout << "BICOLORABLE." << endl;
    else cout << "NOT BICOLORABLE." << endl;
  }
}
