#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;


int main (void) {
  int f, n, a;
  char p[256];
  map<int,string> m;
  map<string,bool> taken;

  m[1] = "qaz";
  m[2] = "wsx";
  m[3] = "edc";
  m[4] = "rfvtgb";
  m[5] = " ";
  m[6] = " ";
  m[7] = "yhnujm";
  m[8] = "ik,";
  m[9] = "ol.";
  m[10] = "p;/";

  string input;
  vector<string> result;

  while (cin >> f >> n) {
    if (n == 0) {
      cout << "0" << endl;
      continue;
    }


    memset(p, (char)1, sizeof(char)*256);
    result.clear();
    taken.clear();

    while (f > 0) {
      cin >> a;

      for (int i = 0; i < m[a].size(); i++) {
	p[m[a][i]] = (char)0;
      }

      f--;
    }

    getline(cin,input); //reading /n

    while (n--) {
      //cin >> input;
      getline(cin,input);

      if (taken[input] == true) continue;
      taken[input] = true;

      bool ok = true;
      for (int i = 0; i < input.size(); i++) {
	if (input[i] < 'a' || input[i] > 'z' || p[input[i]] == 0) {
	  ok = false;
	  break;
	}
      }
      if (ok) result.push_back (input);
    }

    if (result.size() == 0) {
      cout << "0" << endl;
      continue;
    }

    //unique_copy(newres.begin(), newres.end(), result.begin());
    sort(result.begin(), result.end());
    int max = result[result.size()-1].size();

    int counter = 0;
    for (int i = 0; i < result.size(); i++)
      if(result[i].size() == max) counter++;

    cout << counter << endl;
    for (int i = 0 ;i < result.size(); i++)
      if (result[i].size() == max) cout << result[i] << endl;
  }


  return 0;
}
