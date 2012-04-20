#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  string line;
  int people, trees, person, tree;
  while (cases--) {
    /*
     * not using set<int> here, because order and uniqueness of elements is only required after all
     * input is done. Otherwise set would sort/ensure uniqueness on every person => tree pair input
     */
    map<int, vector<int> > opinions;
    cin >> people >> trees;
    getline(cin, line); // read the rest of the "P T" line

    while (cin.peek() != EOF && cin.peek() != '\n') {
      cin >> person >> tree;
      getline(cin, line);
      opinions[person].push_back(tree);
    }

    // turn vectors into sets of unique ids
    vector<vector<int> > sets;
    for (map<int, vector<int> >::iterator o(opinions.begin()), end(opinions.end()); o != end; ++o) {
      vector<int>& t = o->second;
      sort(t.begin(), t.end());
      vector<int>::iterator t_unique_end = unique(t.begin(), t.end());
      t.resize(t_unique_end - t.begin());
      sets.push_back(t);
    }
    sort(sets.begin(), sets.end());

    // include people that haven't heard anything as having same opinion
    cout << distance(sets.begin(), unique(sets.begin(), sets.end())) + (opinions.size() < people) << endl;

    if (cases)
      cout << endl;
  }
  return 0;
}
