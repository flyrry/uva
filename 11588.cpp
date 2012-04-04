#include <iostream>
#include <map>

using namespace std;

typedef map<char, size_t> frequencies;

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  frequencies regions;
  for (int image(1); image <= cases; ++image) {
    regions.clear();
    size_t rows, cols, high, low;
    cin >> rows >> cols >> high >> low;
    string data;
    for (int i(0); i < rows; ++i) {
      cin >> data;
      for (int c(0); c < cols; ++c) {
        ++regions[data[c]];
      }
    }
    size_t max_freq = 0;
    for (frequencies::const_iterator r(regions.begin()), rend(regions.end()); r != rend; ++r)
      max_freq = max(max_freq, r->second);
    size_t filesize = rows * cols * low;
    size_t important = 0;
    for (frequencies::const_iterator r(regions.begin()), rend(regions.end()); r != rend; ++r)
      if (r->second == max_freq) {
        filesize += max_freq * high;
        ++important;
      }

    filesize -= important * max_freq * low;

    cout << "Case " << image << ": " << filesize << endl;
  }
  return 0;
}
