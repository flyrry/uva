#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

typedef long long llong;

int main(void) {
  int g = 34943;
  string line;

  while (getline(cin, line)) {
    if (line == "#") break;

    if (line.size() == 0) {
      cout << "00 00" << endl;
      continue;
    }

    int i = 0;
    llong temp = line[i];

    for (int j = 1; j < line.size(); ++j) {
      temp %= g;
      temp <<= 8;
      temp += line[j];
    }

    temp <<= 16;

    char buf[5];
    sprintf(buf,"%04llX", g - (temp%g));

    cout << buf[0] << buf[1] << " " << buf[2] << buf[3] << endl;
  }
}

