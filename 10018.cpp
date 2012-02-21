/*
 * Cheating with string streams
 */
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

int main(void)
{
//  ios::sync_with_stdio(false);
  int N;
  cin >> N;
  while (N--) {
    uint p;
    cin >> p;
    uint iterations = 0;
    while (true) {
      stringstream ss, ssr;
      ss << p;
      string sp, spr;
      ss >> sp;
      //cout << "sp: " << sp << endl;
      reverse_copy(sp.begin(), sp.end(), back_inserter(spr));
      //cout << "spr: " << spr << endl;
      if (sp == spr) {
        cout << iterations << " " << sp << endl;
        break;
      }
      ssr << spr;
      //cout << "ss: " << ssr.str() << endl;
      uint pr;
      ssr >> pr;
      //cout << "pr: " << pr << endl;
      p += pr;
      //cout << "p: " << p << endl;
      ++iterations;
    }
  }
  return 0;
}
