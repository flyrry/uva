#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define MAX 20000001

int main (void) {
  int i,j;
  int n;
  char *primes;
  vector< pair<int,int> > result;

  primes = (char*)malloc(sizeof(char)*MAX);
  memset(primes, (char)1, sizeof(char)*MAX);
 
  primes[1] = (char)0;

  for (i = 2; i <= (int)sqrt(MAX); i++)
    if (primes[i])
      for (j=i; j*i<MAX;j++) primes[i*j] = 0;

  for (i = 5; i < MAX; i += 2) {
    if (primes[i] == 1 && primes[i-2] == 1) {
      result.push_back (pair<int,int>(i-2,i));
    }
  }

  while (cin >> n) {
    cout << "(" << result[n-1].first << ", " << result[n-1].second << ")" << endl;
  }

  free(primes);

  return 0;
}
