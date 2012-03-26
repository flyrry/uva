#include <string>
#include <iostream>
#include <vector>

using namespace std;

//---------------m
//      |
//      |
//      |
//      n

typedef long long llong;

int main(void) {
	int m, n;
	while (cin >> m >> n) {
		// read matrix
		pair<llong, llong> **matrix = new pair<llong, llong>*[m];
		for (int r = 0; r < m; ++r) {
			matrix[r] = new pair<llong, llong>[n];
			for (int c = 0; c < n; ++c) {
				cin >> matrix[r][c].first;
			}
		}
		
		// compute shortest paths (DP)
		for (int c = n - 1; c >= 0; --c) {
			for (int r = 0; r < m; ++r) {
				if (c == n - 1) // last column
					matrix[r][c].second = matrix[r][c].first;
				else { // pick on of 3
					int x = matrix[r][c+1].second;
					int y = matrix[(r+1)%m][c+1].second;
					int z = matrix[r?r-1:m-1][c+1].second;
					matrix[r][c].second = matrix[r][c].first + min(x,min(y,z));
				}
			}
		}
		
		// find where best path starts
		int row = m - 1;
		int w = matrix[m-1][0].second;
		for (int r = m - 2; r >= 0; --r) {
			if (matrix[r][0].second <= w) {
				w = matrix[r][0].second;
				row = r;
			}
		}
		
		// walk best path
		cout << row + 1;
		for (int c = 0; c < n - 1; ++c) {
			int x = matrix[row?row-1:m-1][c+1].second;
			int y = matrix[row][c+1].second;
			int z = matrix[(row+1)%m][c+1].second;
			
			int s = min(z, min(y, x));
			if (row == m - 1) {
				if (s == z) {cout << " " << 1; row = 0; continue;}
			}
			if (row) {
				if (s == x) {cout << " " << row; --row; continue;}
			}
			if (s == y) {cout << " " << row + 1; continue;}
			if (s == z) {cout << " " << row + 2; ++row; continue;}
			if (s == x) {cout << " " << m; row = m - 1; continue;}
		}
				
		cout << endl << w << endl;
		for (int r = 0; r < m; ++r) {
			delete[] matrix[r];
		}
		delete[] matrix;
	}
	return 0;
}

