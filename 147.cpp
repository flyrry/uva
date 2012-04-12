#include <string>
#include <iostream>

using namespace std;

int main(void) {
	int money[] = {1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};
	long long ways[6001][11];
	
	for (int i = 0; i < 6001; ++i)
		ways[i][0] = 1;

	for (int i = 0; i < 11; ++i)
		ways[0][i] = 1;
	
	for (int x = 1; x < 6001; ++x) {
		for (int y = 1; y < 11; ++y) {
			if (money[y] > x) {
				ways[x][y] = ways[x][y-1];
			} else {
				ways[x][y] = ways[x][y-1] + ways[x-money[y]][y];
			}
		}
	}	
	
	float num;
	while (cin >> num) {
		if (num == 0.0) return 0;
		cout.width(6);
		cout.precision(2);
		cout << fixed << right << num;
		cout.width(17);
		cout << right << ways[(int)(num*20+0.5)][10] << endl;
	}
	return 0;
}

