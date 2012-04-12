#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

double compute_h(double d, double t) {
  double e = 6.11 * exp(5417.7530 * ((1/273.16) - (1/(d+273.16))));
  return t + (0.5555) * (e-10.0);
}

double compute_d(double t, double hum) {
  double h = hum - t;
  double e = h/0.5555 + 10.0;
  return 5417.7530/(5417.7530/273.16 - log(e/6.11)) - 273.16;
}

double compute_t(double d, double hum) {
  double e = 6.11 * exp(5417.7530 * ((1/273.16) - (1/(d+273.16))));
  double h = (0.5555) * (e-10.0);
  return hum - h;
}

int main(void) {
  string input;
  stringstream ss;
  char c;
  double t,d,h;
  bool _t, _d, _h;

  while (getline(cin,input)) {
    if (input == "E") break;

    ss.str(string());
    ss.clear();

    ss << input;
    _t = _d = _h = false;
    while (ss >> c) {
      switch(c) {
	case 'T':
	  ss >> t;
	  _t = true;
	  break;
	case 'D':
	  ss >> d;
	  _d = true;
	  break;
	case 'H':
	  ss >> h;
	  _h = true;
	  break;
      }
    }

    if (!_d) d = compute_d(t,h);
    else if (!_t) t = compute_t(d,h);
    else if (!_h) h = compute_h(d,t);

    cout << fixed << setprecision(1) << "T " << t << " D " << d << " H " << h << endl;
  }
  return 0;
}
