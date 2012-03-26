#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string, string> nodes;

bool scomp(string f, string s) {
  if (f.size() != s.size())
    return f.size() < s.size();
  return lexicographical_compare(f.begin(), f.end(), s.begin(), s.end());
}

void walk() {
  vector<string> paths;
  for (map<string, string>::iterator i(nodes.begin()), end(nodes.end()); i != end; ++i)
    paths.push_back(i->first);

  for (vector<string>::iterator i(paths.begin()), end(paths.end()); i != end; ++i) {
    if (i->size() > 0 && find(paths.begin(), paths.end(), i->substr(0, i->size()-1)) == paths.end()) {
      cout << "not complete" << endl;
      return;
    }
  }
  sort(paths.begin(), paths.end(), scomp);
  vector<string>::iterator i(paths.begin());
  cout << nodes[*i];
  for(++i; i != paths.end(); ++i) {
    cout << " " << nodes[*i];
  }
  cout << endl;
}

int main(void) {
  char c;
  while (true) {
    bool broken = false;
    while (cin.good()) {
      cin.get(c);
      if (c == '(') {
        string val,path;
        if (cin.peek() == ')') {
          if (broken || nodes.empty()) cout << "not complete" << endl;
          else walk();
          nodes.clear();
          break;
        } else {
          while (cin.get(c)) {
            if (c == ',')
              break;
            val += c;
          }
          while (cin.get(c)) {
            if (c == ')')
              break;
            path += c;
          }
        }
        if (val.empty() || !nodes[path].empty()) {
          broken = true;
        }
        nodes[path] = val;
      }
    }
    if (!cin.good()) return 0;
  }
}
