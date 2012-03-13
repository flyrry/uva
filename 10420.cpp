#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  typedef set<string> countries_set;
  countries_set countries;
  map<string, set<string> > all_the_single_ladies;
  while (n--) {
    string country, name;
    cin >> country;
    getline(cin, name);
    countries.insert(country);
    all_the_single_ladies[country].insert(name);
  }
  for (countries_set::iterator I = countries.begin(); I != countries.end(); ++I)
    cout << *I << " " << all_the_single_ladies[*I].size() << endl;
  return 0;
}
