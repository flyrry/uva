#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

map<char,char> keys;

string decode(string& num) {
  string ret = "";
  for (int i = 0; i < num.size(); ++i) {
    if (ret.size() == 3) ret += '-';
    if (num[i] == '-' || num[i] == 'Q' || num[i] == 'Z') continue;
    if (num[i] >= 'A' && num[i] < 'Z') {
      ret += keys[num[i]];
    } else {
      ret += num[i];
    }
  }
  return ret;
}

int main(void) {
  int cases, numbers;
  string number;
  map<string, int> dup;
  vector<string> res;
  cin >> cases;
  keys['A'] = keys['B'] = keys['C'] = '2';
  keys['D'] = keys['E'] = keys['F'] = '3';
  keys['G'] = keys['H'] = keys['I'] = '4';
  keys['J'] = keys['K'] = keys['L'] = '5';
  keys['M'] = keys['N'] = keys['O'] = '6';
  keys['P'] = keys['R'] = keys['S'] = '7';
  keys['T'] = keys['U'] = keys['V'] = '8';
  keys['W'] = keys['X'] = keys['Y'] = '9';
  while (cases--) {
    dup.clear();
    res.clear();
    cin >> numbers;
    while (numbers--) {
      cin >> number;
      ++dup[decode(number)];
    }
    for (map<string, int>::iterator i(dup.begin()), end(dup.end()); i != end; ++i)
      if (i->second > 1) res.push_back(i->first);

    if (res.empty()) {
      cout << "No duplicates." << endl;
    } else {
      sort(res.begin(),res.end());
      for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << " " << dup[res[i]] << endl;
      }
    }
    if (cases) cout << endl;
  }
  return 0;
}
