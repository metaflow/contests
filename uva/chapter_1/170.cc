#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s; int i;
  while (cin >> s, s != "#") {
    vector<queue<string>> decks(13);
    decks[0].push(s);
    for (i = 1; i < 52; i++) {
      cin >> s;
      decks[i % 13].push(s);
    }
    i = 0;
    s = "";
    int count = 0;
    while (!decks[i].empty()) {
      count++;
      s = decks[i].front(); decks[i].pop();
      switch (s[0]) {
        case 'K': i = 0; break;
        case 'Q': i = 1; break;
        case 'J': i = 2; break;
        case 'T': i = 3; break;
        case '9': i = 4; break;
        case '8': i = 5; break;
        case '7': i = 6; break;
        case '6': i = 7; break;
        case '5': i = 8; break;
        case '4': i = 9; break;
        case '3': i = 10; break;
        case '2': i = 11; break;
        case 'A': i = 12; break;
      }
    }
    printf("%02d,%s\n", count, s.c_str());
  }
}
