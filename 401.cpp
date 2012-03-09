#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
  char mirrors[256];
  memset(mirrors, 0, sizeof(char)*256);
  mirrors['A'] = 'A';
  mirrors['E'] = '3';
  mirrors['H'] = 'H';
  mirrors['I'] = 'I';
  mirrors['J'] = 'L';
  mirrors['L'] = 'J';
  mirrors['M'] = 'M';
  mirrors['O'] = 'O';
  mirrors['S'] = '2';
  mirrors['T'] = 'T';
  mirrors['U'] = 'U';
  mirrors['V'] = 'V';
  mirrors['W'] = 'W';
  mirrors['X'] = 'X';
  mirrors['Y'] = 'Y';
  mirrors['Z'] = '5';
  mirrors['1'] = '1';
  mirrors['2'] = 'S';
  mirrors['3'] = 'E';
  mirrors['5'] = 'Z';
  mirrors['8'] = '8';
  ios::sync_with_stdio(false);
  string in;
  while (cin >> in) {
    bool palindrome = true;
    bool mirrored = true;
    for (int i = 0, length = in.length(), middle = length / 2; i <= middle; ++i) {
      char l = in[i];
      char r = in[length - i - 1];
      palindrome &= (l == r);
      mirrored &= (l == mirrors[r]);
    }
    cout << in;
    if (mirrored && palindrome)
      cout << " -- is a mirrored palindrome.";
    else if (mirrored)
      cout << " -- is a mirrored string.";
    else if (palindrome)
      cout << " -- is a regular palindrome.";
    else
      cout << " -- is not a palindrome.";
    cout << endl << endl;
  }
  return 0;
}
