#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  string plain, encrypted;
  while (cin >> plain >> encrypted) {
    const char* s = plain.c_str(); // need the terminating '\0'
    const char* t = encrypted.data();
    for (size_t i = 0, length = encrypted.length(); i != length; ++i)
      if (*s == *t++) s++;
    if (*s)
      cout << "No" << endl;
    else
      cout << "Yes" << endl;
  }
  return 0;
}
