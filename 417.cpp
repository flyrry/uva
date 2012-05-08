#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef vector<string> wordlist;

bool word_cmp(const string& lhs, const string& rhs) {
  if (lhs.size() == rhs.size()) return lhs < rhs;
  return lhs.size() < rhs.size();
}

void generate(const string& base, char suffix, wordlist& list, int depth) {
  for (char i(suffix); i <= 'z'; ++i) {
    string ns = base + i;
    if (depth) generate(ns, i+1, list, depth - 1);
    list.push_back(string(ns));
  }
}

int main()
{
  ios::sync_with_stdio(false);

  wordlist valid_words;
  generate("", 'a', valid_words, 4);

  sort(valid_words.begin(), valid_words.end(), word_cmp);

  string word;
  while (cin >> word) {
    wordlist::iterator i = find(valid_words.begin(), valid_words.end(), word);
    if (i != valid_words.end())
      cout << distance(valid_words.begin(), i) + 1;
    else
      cout << "0";
    cout << endl;
  }

  return 0;
}
