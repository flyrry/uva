#include <iostream>
#include <map>
#include <vector>

using namespace std;

inline bool isproject(string& str) {
  return isupper(str[0]);
}

bool mycmp(const pair<string, int>& a, const pair<string, int>& b) {
  if (a.second != b.second) return a.second > b.second;
  else return a.first < b.first;
}

int main(void) {
  typedef map<string, map<string, int> > MAP;
  map<string, map<string, int> > users;
  map<string, int> projects;
  vector<pair<string,int> >vec;
  string user, prj;
  while (cin.peek() != '0') {

    users.clear();
    projects.clear();
    vec.clear();

    while (cin.peek() != '1') {
      getline(cin, prj);
      projects[prj] = 0;
      while (isalpha(cin.peek()) && !isupper(cin.peek())) {
        getline(cin, user);
        users[user][prj] = 1;
      }
    }
    getline(cin, user);

    for (MAP::iterator I=users.begin(); I!=users.end(); ++I) {
      if (I->second.size() > 1) continue;
      for (map<string, int>::iterator P=I->second.begin(); P!= I->second.end(); ++P) {
        ++projects[P->first];
      }
    }

    for (map<string, int>::iterator I=projects.begin(); I!=projects.end(); ++I) {
      vec.push_back(pair<string, int>(I->first, I->second));
    }

    sort(vec.begin(), vec.end(), mycmp);

    for (vector<pair<string, int> >::iterator I=vec.begin(); I!=vec.end(); ++I) {
      cout << I->first << " " << I->second << endl;
    }
  }
  return 0;
}
