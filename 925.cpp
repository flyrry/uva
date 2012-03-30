#include <iostream>
#include <set>
#include <map>
#include <list>

using namespace std;

struct course;
typedef set<course*> courses_t;
struct course {
  courses_t required;
  string name;
};

typedef map<string, course> prerequisites_t;

int main()
{
  ios::sync_with_stdio(false);
  size_t c;
  cin >> c;
  prerequisites_t prereq;
  while (c--) {
    prereq.clear();
    size_t k;
    cin >> k;
    string name;
    while (k--) {
      cin >> name;
      prereq[name].name = name;
    }
    size_t j;
    cin >> j;
    while (j--) {
      cin >> name;
      cin >> k; // nr of prerequisites
      string pname;
      while (k--) {
        cin >> pname;
        prereq[name].required.insert(&prereq[pname]);
      }
    }
    // output
    for (prerequisites_t::const_iterator pi(prereq.begin()), pend(prereq.end()); pi != pend; ++pi) {
      if (pi->second.required.size()) { // has requirements
        set<string> requirements;
        list<course*> extras;
        for (courses_t::const_iterator ri(pi->second.required.begin()), rend(pi->second.required.end()); ri != rend; ++ri) {
          requirements.insert((*ri)->name);
          copy((*ri)->required.begin(), (*ri)->required.end(), back_inserter(extras));
        }

        for (course* c; !extras.empty(); extras.pop_front()) {
          c = extras.front();
          copy(c->required.begin(), c->required.end(), back_inserter(extras));
          requirements.erase(c->name);
        }

        cout << pi->first << " " << requirements.size();
        for (set<string>::const_iterator ri(requirements.begin()), rend(requirements.end()); ri != rend; ++ri)
          cout << " " << *ri;
        cout << endl;
      }
    }
  }
  return 0;
}
