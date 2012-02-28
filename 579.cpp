/*
 * minute hand turns 360 degrees in 60 minutes => 6 degrees per minute
 * hour hand turns 360 degrees in 12 hours (720 minutes) => 0.5 degrees per minute
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  while (true) {
    double hours, minutes;
    cin >> hours;
    cin.ignore(1, ':');
    cin >> minutes;

    if (!hours&&!minutes) break;

    // hours hand angle => (H * 60 + M) * 0.5
    // minutes hand angle => M * 6
    // ((H * 60 + M) * 0.5 - M * 6) => 30 * H - 5.5 * M
    double difference = abs(30 * hours - 5.5 * minutes);

    cout << fixed << setprecision(3) << abs(min(difference, 360-difference)) << endl;
  }
  return 0;
}
