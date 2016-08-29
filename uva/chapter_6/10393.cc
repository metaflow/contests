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
  vector<string> letters = {"qaz",
    "wsx",
    "edc",
    "rfvtgb",
    "",
    "",
    "yhnujm",
    "ik",
    "ol",
    "p"
    };
  vector<int> char_finger(26);
  for (int i = 0; i < 10; ++i) {
    for (auto c : letters[i]) char_finger[c - 'a'] = i;
  }
  int n, f;
  while (cin >> f >> n) {
    bitset<10> injured;
    injured.reset();
    while (f--) {
      int i;
      cin >> i;
      injured[i - 1] = true;
    }
    vector<string> words(n);
    while (n--) cin >> words[n];
    sort(words.begin(), words.end());
    vector<string> answer;
    size_t best = 0;
    string last = "";
    for (auto w : words) {
      if (w == last) continue;
      last = w;
      bool ok = true;
      for (auto c : w) ok = ok && (!injured[char_finger[c - 'a']]);
      if (!ok) continue;
      if (w.size() > best) {
        answer.clear();
        best = w.size();
      }
      if (w.size() == best) answer.emplace_back(w);
    }
    cout << answer.size() << endl;
    for (auto w : answer) {
      cout << w << endl;
    }
  }
}

// time : 22:22
