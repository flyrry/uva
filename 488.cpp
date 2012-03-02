#include <iostream>

using namespace std;

const char* lines[] = {"1\n",
                       "22\n",
                       "333\n",
                       "4444\n",
                       "55555\n",
                       "666666\n",
                       "7777777\n",
                       "88888888\n",
                       "999999999\n"};

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  int amplitude;
  size_t frequency;
  while (cases--) {
    cin >> amplitude >> frequency;
    for (size_t i = 0; i < frequency; ++i) {
      if (i)
        cout << endl;
      for (int j = 0; j < amplitude; ++j)
        cout << lines[j];
      for (int j = amplitude - 2; j >= 0; --j)
        cout << lines[j];
    }
    if (cases)
      cout << endl;
  }
  return 0;
}
