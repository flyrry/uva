#include <iostream>
#include <limits>

using namespace std;

int i,j,a,dim,k,max_h,max_v,min_v,min_h;
int min_hp, min_vp, max_vp, max_hp;
int** input;
int** dp;

int main(void) {
  while(cin >> dim) {

    input = new int*[dim];
    for(i = 0; i < dim; i++) input[i] = new int[dim];

    for(i = 0; i < dim; i++) {
      for(j = 0; j < dim; j++) {
	cin >> a;
	input[i][j] = a;
      }
    }

    dp = new int*[dim+2];
    for(i = 0; i < dim+2; i++) dp[i] = new int[dim+2];

    for(i = 0; i < dim+2; i++) { dp[i][0] = 0; dp[0][i] = 0; dp[i][dim+1] = INT_MIN; dp[dim+1][i] = INT_MIN; }

    
    for(i = 1; i < dim+1; i++) {
      for(j = 1; j < dim+1; j++) {
	dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + input[i-1][j-1];
      }
    }


    /*for (i = 0; i < dim+1; i++) {
      for (j = 0; j < dim+1; j++) {
	cout << dp[i][j] << " ";
      }
      cout << endl;
    }
    return 0;*/

    min_v = min_h = INT_MAX;
    max_v = max_h = INT_MIN;

    for(i = dim; i > 0; i--) {
      for(j = dim; j > 0; j--) {
	for(k = j-1; k >= 0; k--) {
	  if(dp[i][j] - dp[i][k] > max_h) max_h = dp[i][j] - dp[i][k];
	}
	dp[i][dim+1] = max(max_h,dp[i][dim+1]);
	max_h = INT_MIN;
      }
    }

    for(i = dim; i > 0; i--) {
      for(j = dim; j > 0; j--) {
	for(k = i-1; k >= 0; k--) {
	  if(dp[i][j] - dp[k][j] > max_v) max_v = dp[i][j] - dp[k][j];
	}
	dp[dim+1][j] = max(max_v,dp[dim+1][j]);
	max_v = INT_MIN;
      }
    }

    max_v = INT_MIN;
    for(i = dim; i > 0; i--)
      if(dp[i][dim+1] > max_v) { max_v = dp[i][dim+1]; max_vp = i; }

    min_v = INT_MAX;
    min_vp = max_vp;
    for(i = max_vp; i > 0; i--)
      if(dp[i][dim+1] < min_v) { min_v = dp[i][dim+1]; min_vp = i; }

    for(j = dim; j > 0; j--) 
      if(dp[dim+1][j] > max_h) { max_h = dp[dim+1][j]; max_hp = j; }

    min_h = INT_MAX;
    min_hp = max_hp;
    for(j = max_hp; j > 0; j--) 
      if(dp[dim+1][j] < min_h) { min_h = dp[dim+1][j]; min_hp = j; }

    //cout << max_h << " " <<  max_v << endl;
    //cout << min_h << " " <<  min_v << endl;
    for (i = 0; i < dim+2; i++) {
      for (j = 0; j < dim+2; j++) {
	cout << dp[i][j] << " ";
      }
      cout << endl;
    }

    cout << "maxh: " << max_hp << " " << "minh: " << min_hp << endl;
    cout << "maxv: " << max_vp << " " << "minv: " << min_vp << endl;


    //cout << "ANWER: " << dp[max_vp][max_hp] << " + " << dp[min_vp-1][min_hp] << " - " << dp[max_vp][min_hp-1] << " - " << dp[min_vp-1][max_hp-1] << endl;

    cout << dp[max_vp][max_hp] << " + " << dp[min_vp][min_hp] << " - " << dp[max_vp][min_hp] << " - " << dp[min_vp][max_hp] << endl;
    cout << dp[max_vp][max_hp] + dp[min_vp][min_hp] - dp[max_vp][min_hp] - dp[min_vp][max_hp] << endl;

    return 0;














    for(i = 0; i < dim; i++) delete[] dp[i];
    delete[] dp;
  }
  return 0;
}
