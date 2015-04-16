#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  int duration;
  unsigned records;
  double downpayment, loan;
  vector<double> depreciations(101, 0);
  //depreciations.reserve(100);

  while (cin >> duration >> downpayment >> loan >> records) {
    if (duration < 0)
      break;

    unsigned last_month = 0;
    depreciations[0] = 0;

    for (unsigned r = 0; r < records; ++r) {
      unsigned month;
      double depreciation;

      cin >> month >> depreciation;
      unsigned timespan = month - last_month;
      if (timespan > 1) {
        fill(depreciations.begin() + last_month+1, depreciations.begin() + month, depreciations[last_month]);
      }

      depreciations[month] = depreciation;
      last_month = month;
    }

    if (last_month < duration)
      fill(depreciations.begin() + last_month+1, depreciations.begin() + duration, depreciations[last_month]);

    double value = loan + downpayment;
    double payment = loan / duration;

    unsigned month = 0;
    for (; month < duration; ++month) {
      value *= (1.0 - depreciations[month]);
      if (month) loan -= payment;
      if (loan < value)
        break;
    }

    if (month == 1)
      cout << "1 month" << endl;
    else
      cout << month << " months" << endl;
  }
  return 0;
}
