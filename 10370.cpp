#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
  size_t cases;
  cin >> cases;
  while (cases--) {
    size_t students, grade;
    size_t grades[1000];
    cin >> students;
    size_t total = 0;
    for (int i = 0; i < students; ++i) {
      cin >> grade;
      total += grade;
      grades[i] = grade;
    }

    double average = (double)total / students;

    size_t above = 0;
    for (int i = 0; i < students; ++i) {
      if (grades[i] > average)
        above++;
    }
    cout << fixed << setprecision(3) << (double)above/students*100.0 << "%" << endl;
  }
  return 0;
}
