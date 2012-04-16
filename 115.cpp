#include <iostream>
#include <string>
#include <map>
#include <cstring>

using namespace std;

#define NODES 310

typedef map<string, int> node_index;

int main()
{
  ios::sync_with_stdio(false);
  string lhs, rhs;
  node_index glossary;
  int parent[NODES];

  int id = 0;

  memset(parent, 0, sizeof(int) * NODES);

  // build tree
  while (cin >> lhs >> rhs) {
    if (lhs == "no.child")
      break;

    if (!glossary.count(lhs)) {
      glossary[lhs] = ++id;
    }
    if (!glossary.count(rhs)) {
      glossary[rhs] = ++id;
    }

    // set relation
    parent[glossary[lhs]] = glossary[rhs];
  }

  while (cin >> lhs >> rhs) {
    // locate lhs and rhs
    const int l = (glossary.count(lhs) ? glossary[lhs] : 0);
    const int r = (glossary.count(rhs) ? glossary[rhs] : 0);

    // any of them doesn't exist in the tree
    if (!l || !r) {
      cout << "no relation" << endl;
      continue;
    }

    // l and r are in different trees
    register int ll = l, rr = r;
    while (ll) ll = parent[ll];
    while (rr) rr = parent[rr];
    if (ll != rr) {
      cout << "no relation" << endl;
      continue;
    }

    // check if parent
    int depth = 0;
    bool found = false;
    ll = l;
    rr = r;
    while (parent[rr]) {
      if (parent[rr] == ll) {
        found = true;
        break;
      }
      rr = parent[rr];
      ++depth;
    }
    if (found) {
      if (depth == 0)
        cout << "parent" << endl;
      else if (depth == 1)
        cout << "grand parent" << endl;
      else {
        for (int i(1); i < depth; ++i)
          cout << "great ";
        cout << "grand parent" << endl;
      }
      continue;
    }

    // check if child
    depth = 0;
    found = false;
    ll = l;
    rr = r;
    while (parent[ll]) {
      if (parent[ll] == rr) {
        found = true;
        break;
      }
      ll = parent[ll];
      ++depth;
    }
    if (found) {
      if (depth == 0)
        cout << "child" << endl;
      else if (depth == 1)
        cout << "grand child" << endl;
      else {
        for (int i(1); i < depth; ++i)
          cout << "great ";
        cout << "grand child" << endl;
      }
      continue;
    }

    // check if sibling
    if (parent[l] && parent[r] && parent[l] == parent[r]) {
      cout << "sibling" << endl;
      continue;
    }

    // check if cousin
    register int n = 0, m = 0;  
    ll = l;
    rr = r;
    while (parent[ll]) {
      ll = parent[ll];
      ++n;
    }
    while (parent[rr]) {
      rr = parent[rr];
      ++m;
    }
    ll = l; // reset to original
    rr = r;
    int depthN = n, depthM = m;  

    if (n == m) {
      while (parent[ll] != parent[rr]) {
        ll = parent[ll];
        rr = parent[rr];
        --n;
      }

      cout << (depthN - n) << " cousin" << endl;
    } else {
      if (m > n) {
        swap(m, n);
        swap(ll, rr);
        swap(depthN, depthM);
      }

      while (n > m) { ll = parent[ll]; --n; }
      while (parent[ll] != parent[rr]) {
        ll = parent[ll];
        rr = parent[rr];
        --n;
      }
      depthN -= n;  
      depthM -= n;  

      cout << depthM << " cousin removed " << (depthN - depthM) << endl;
    }
  }
  return 0;
}
