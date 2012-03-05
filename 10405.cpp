/*
 * longest common subsequence
 * (optimized to only compute LCS length)
 *
 * note: string apparently may contain spaces, hence the ugly IO
 */
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t lcs_table[1001][1001]; // ~3.8mb
  string first, second;
  memset(lcs_table, 0, sizeof(size_t) * 1001 * 1001);
  int i, k, first_length, second_length;
  while (true) {
    getline(cin, first);
    getline(cin, second);
    if (!cin) break;
    for (i = 1, first_length = first.length() + 1; i != first_length; ++i) {
      for (k = 1, second_length = second.length() + 1; k != second_length; ++k) {
        if (first[i-1] == second[k-1]) {
          lcs_table[i][k] = lcs_table[i-1][k-1] + 1;
        } else {
          lcs_table[i][k] = max(lcs_table[i-1][k], lcs_table[i][k-1]);
        }
      }
    }
    cout << lcs_table[i-1][k-1] << endl;
  }
  return 0;
}
