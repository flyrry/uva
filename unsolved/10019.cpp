#include <iostream>

using namespace std;

// count '1' bits
inline short ones_count(short m)
{
  short bits = 0;
  bits += !!(m & 0x0001);
  bits += !!(m & 0x0002);
  bits += !!(m & 0x0004);
  bits += !!(m & 0x0008);
  bits += !!(m & 0x0010);
  bits += !!(m & 0x0020);
  bits += !!(m & 0x0040);
  bits += !!(m & 0x0080);
  bits += !!(m & 0x0100);
  bits += !!(m & 0x0200);
  bits += !!(m & 0x0400);
  bits += !!(m & 0x0800);
  bits += !!(m & 0x1000);
  bits += !!(m & 0x2000);
  bits += !!(m & 0x4000);
  bits += !!(m & 0x8000);
}

// return number as if it was given in hex representation
// max possible input is 9999
inline short as_hex(short m)
{
  short hex = 0, tail, digit;
  tail = m % 10; // 999[9]
  hex += tail;

  tail += digit = (m - tail) % 100; // 9990 % 100
  digit /= 10; // 99[9]9
  hex += digit * 0x10;

  tail += digit = (m - tail) % 1000;
  digit /= 100; // 9[9]99
  hex += digit * 0x100;

  tail += digit = (m - tail);
  digit /= 1000; // [9]999
  hex += digit * 0x1000;

  return hex;
}

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  short m;
  while (cases--) {
    cin >> m;
    cout << ones_count(m) << " " << ones_count(as_hex(m)) << endl;
  }
  return 0;
}
