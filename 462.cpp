#include <iostream>

using namespace std;

typedef struct {
  char rank;
  char suit;
} card_t;

int main()
{
  ios::sync_with_stdio(false);
  string line;
  while (getline(cin, line)) {
    card_t cards[13];
    int suits['S'+1];
    bool stopped['S'+1];
    suits['S'] = suits['H'] = suits['D'] = suits['C'] = 0;
    stopped['S'] = stopped['H'] = stopped['D'] = stopped['C'] = false;


    for (int i = 0; i < 13; ++i) {
      cards[i].rank = line[i*3];
      cards[i].suit = line[i*3+1];
      ++suits[cards[i].suit];
    }

    int points = 0;

    // rule 1
    for (int i = 0; i < 13; ++i) {
      switch(cards[i].rank) {
        case 'A':
          points += 4;
          stopped[cards[i].suit] = true;            // stopped rule
          break;
        case 'K':
          points += 3;
          if (suits[cards[i].suit] <= 1) --points;  // rule 2
          else stopped[cards[i].suit] = true;       // stopped rule
          break;
        case 'Q':
          points += 2;
          if (suits[cards[i].suit] <= 2) --points;  // rule 3
          else stopped[cards[i].suit] = true;       // stopped rule
          break;
        case 'J':
          ++points;
          if (suits[cards[i].suit] <= 3) --points;  // rule 4
          break;
      }
    }

    // rules 5, 6, 7
    int extra_points = 0;
    char kinds[] = {'S', 'H', 'D', 'C'};
    char max_kind;
    int max_suit = 0;
    for (int i = 0; i < 4; ++i) {
      if (suits[kinds[i]] == 2) ++extra_points;
      if (suits[kinds[i]] <= 1) extra_points += 2;
      if (suits[kinds[i]] > max_suit) {
        max_suit = suits[kinds[i]];
        max_kind = kinds[i];
      }
    }

    int total = points + extra_points;
    if (points >= 16 && stopped['S'] && stopped['H'] && stopped['D'] && stopped['C'])
      cout << "BID NO-TRUMP" << endl;
    else if (total < 14)
      cout << "PASS" << endl;
    else
      cout << "BID " << max_kind << endl;
  }

  return 0;
}
