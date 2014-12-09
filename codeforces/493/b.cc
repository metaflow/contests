#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  while (cin >> n) {
    ll sum_a = 0, sum_b = 0;
    vi a, b;
    int move;
    while (n--) {
      cin >> move;
      if (move > 0) {
        a.emplace_back(move);
        sum_a += move;
      } else {
        b.emplace_back(-move);
        sum_b -= move;
      }
    }
    ll winner = 0;
    if (sum_a != sum_b) {
      winner = sum_a - sum_b;
    } else {
      for (int i = 0; i < min(a.size(), b.size()); i++) {
        if (a[i] == b[i]) continue;
        winner = a[i] - b[i];
        break;
      }
      if (winner == 0) winner = move;
    }
    if (winner > 0) {
      cout << "first" << endl;
    } else {
      cout << "second" << endl;
    }
  }
}
