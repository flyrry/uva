#include <cstdio>
#include <vector>

using namespace std;

typedef vector<char> roll_list;

inline short valueof(char c) {
  return (c == 'X') ? 10 : (c == '/') ? 10 : c - '0';
}

short compute_score(roll_list& rolls) {
  short score = 0;
  short frames = 0;
  for (int i = 0, size(rolls.size()); frames < 20; ++i) {
    if (rolls[i] == 'X') {
      if (rolls[i+2] == '/')
        score += 20;
      else
        score += 10 + valueof(rolls[i+1]) + valueof(rolls[i+2]);
      frames += 2;
    } else if (rolls[i] == '/') {
      score += 10 - valueof(rolls[i-1]) + valueof(rolls[i+1]);
      ++frames;
    } else {
      score += valueof(rolls[i]);
      ++frames;
    }
  }
  return score;
}

int main()
{
  roll_list rolls;
  char c;
  while ((c = getchar_unlocked()) != EOF) {
    if (c == '\n') {
      printf("%d\n", compute_score(rolls));
      rolls.clear();
      continue;
    }
    else if (c == ' ') continue;
    else if (c == 'G') break;
    else rolls.push_back(c);
  }

  return 0;
}
