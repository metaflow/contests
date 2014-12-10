#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

class GreaterGame {
public:
  double calc(vector <int> hand, vector <int> sothe) {
    int n = sothe.size();
    sort(hand.begin(), hand.end());
    sort(sothe.begin(), sothe.end());
    bitset<100> used;
    used.reset();
    for (auto i : hand) used[i] = true;
    double r = 0;
    for (auto i : sothe) {
      if (i == -1) continue;
      used[i] = true;
      auto a = lower_bound(hand.begin(), hand.end(), i);
      if (a == hand.end()) {
        hand.erase(hand.begin());
      } else {
        r += 1;
        hand.erase(a);
      }
    }
    vector<int> left;
    for (int i = 1; i <= 2 * n; i++) {
      if (used[i]) continue;
      left.emplace_back(i);
    }


    for (auto i : hand) {
      auto a = lower_bound(left.begin(), left.end(), i);
      r += ((double)(a - left.begin())) / hand.size();
    }
    return r;
  }
};

int main() {
  GreaterGame gg;
  cerr << gg.calc({4,2}, {1,3}) << endl;
  cerr << gg.calc({4,2}, {-1,-1}) << endl;
  cerr << gg.calc({1,3,5,7}, {8,-1,4,-1}) << endl;
  cerr << gg.calc({6,12,17,14,20,8,16,7,2,15}, {-1,-1,4,-1,11,3,13,-1,-1,18}) << endl;
}
