#include <iostream>

using namespace std;

#define MAX_SELF_NUMBER 1000001

bool numbers[MAX_SELF_NUMBER];

size_t d(size_t i) {
  size_t result = i;
  while (i) {
    result += i % 10;
    i /= 10;
  }
  return result;
}

int main()
{
  ios::sync_with_stdio(false);
  for (size_t i(1); i < MAX_SELF_NUMBER; ++i) {
    numbers[d(i)] = true;
  }

  for (int i(1); i < MAX_SELF_NUMBER; ++i)
    if (!numbers[i]) cout << i << "\n";
  return 0;
}
