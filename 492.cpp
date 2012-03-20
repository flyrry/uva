#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef enum { AY, XAY, NONE } PLE; // pig-latin ending

int main()
{
  ios::sync_with_stdio(false);
  char vowel_array[] = {'a', 'A', 'o', 'O', 'u', 'U', 'i', 'I', 'e', 'E'};
  vector<char> vowels(vowel_array, vowel_array + sizeof(vowel_array)/sizeof(char));
  sort(vowels.begin(), vowels.end());
  char c, first_letter;
  bool space = true;
  PLE ending = NONE;
  while (cin.get(c)) {
    if (c >= 'A' && c <= 'z') {
      if (space) {
        if (binary_search(vowels.begin(), vowels.end(), c))
          ending = AY;
        else {
          ending = XAY;
          space = false;
          first_letter = c;
          continue;
        }
      }
      space = false;
    } else {
      if (!space) {
        switch (ending) {
          case AY:
            cout << "ay"; break;
          case XAY:
            cout << first_letter << "ay"; break;
          default: break;
        }
      }
      space = true;
    }
    cout.put(c);
  }
  return 0;
}
