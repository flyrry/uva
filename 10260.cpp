#include <iostream>
#include <string>

using namespace std;

char soundex_code_for(char c) {
      switch (c) {
        case 'B': case 'F': case 'P': case 'V':
          return '1';
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z':
          return '2';
        case 'D': case 'T':
          return '3';
        case 'L':
          return '4';
        case 'M': case 'N':
          return '5';
        case 'R':
          return '6';
        default:
          return 0;
          break;
      }
}

string soundex(const string& word) {
  string sum;
  char last(0);
  for (int i(0), length(word.length()); i < length; ++i) {
    char code = soundex_code_for(word[i]);
    if (code && (code != last)) {
      sum += code;
    }
    last = code;
  }
  return sum;
}

int main()
{
  ios::sync_with_stdio(false);
  string word;
  while (cin >> word)
    cout << soundex(word) << endl;
  return 0;
}
