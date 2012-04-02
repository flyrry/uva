#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  double height, up, down, fatique;
  while (cin >> height >> up >> down >> fatique) {
    if (!height)
      break;
    double distance = 0;
    size_t day = 0;
    for (; distance >= 0; ++day) {
      distance += max(up - up / 100 * fatique * day, 0.0);
      if (distance > height) {
        cout << "success on day " << day + 1 << endl;
        break;
      }
      distance -= down;
    }

    if (distance < 0)
      cout << "failure on day " << day << endl;
  }
  return 0;
}
