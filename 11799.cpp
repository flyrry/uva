#include <iostream>
#include <list>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);

  size_t cases, i = 0;
  cin >> cases;
  while (cases--) {
    size_t students;
    cin >> students;
    list<size_t> speeds;
    while (students--) {
      size_t speed;
      cin >> speed;
      speeds.push_back(speed);
    }
    speeds.sort();
    cout << "Case " << ++i << ": " << speeds.back() << endl;
  }
  return 0;
}
