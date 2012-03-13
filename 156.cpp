#include <iostream>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);

  typedef map<string, pair<string, size_t> > wordmap;
  wordmap originals;
  list<string> anagramless;
  string mixed_case_word;
  while (cin >> mixed_case_word) {
    if (mixed_case_word == "#")
      break;
    string word(mixed_case_word);
    transform(mixed_case_word.begin(), mixed_case_word.end(), word.begin(), ::tolower);
    sort(word.begin(), word.end());
    if (originals.count(word))
      originals[word] = make_pair(mixed_case_word, 0);
    else
      originals[word] = make_pair(mixed_case_word, 1);
  }

  for (wordmap::iterator I = originals.begin(); I != originals.end(); ++I)
    if (I->second.second)
      anagramless.push_back(I->second.first);

  anagramless.sort();

  while (!anagramless.empty()) {
    cout << anagramless.front() << endl;
    anagramless.pop_front();
  }

  return 0;
}
