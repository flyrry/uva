#include <iostream>
int count = 0;

bool find_chars(char* from, char* to, int sz) {
  bool found = false;
  for(int i=0; i<sz; i++) {
    for(int k=0; k<sz; k++) {
      if(from[i] == to[k]) {
	to[k] = 'X';
	found = true;
	break;
      }
    }
    if(!found) return false;
    found = false;
  }
  return true;
}

int main(void) {
  int res;
  char from[9];
  char to[9];
  //2
  
  for(int i=100; i<1000; i++) {
    for(int k=100; k<1000; k+=2) {
      res = i*k;
      if(res%2) continue;
      sprintf(from, "%d%d", i, k);
      
      sprintf(to, "%d", res);
      if(find_chars(from, to, 6)) {
	printf("%d %d %d\n", i, k, res);
      }
    }
  }
      printf("%d\n", count);
  return 0;
}
