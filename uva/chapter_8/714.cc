#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 500;

// invariant: answer is within (a, b], f(a) = false, f(b) = true
ll binary_search_lower(ll a, ll b, function<bool(ll)> f) {
  while (b - a > 1) {
    ll m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int m, k;
    cin >> m >> k;
    ll books[MAX];
    ll b = 0, t = 0;
    for (int i = 0; i < m; i++) {
      cin >> books[i];
      b = max(b, books[i] - 1);
      t += books[i];
    }
    t = binary_search_lower(b, t, [&] (ll x) {
      int i = 0;
      for (int j = 0; j < k; j++) {
        int a = 0;
        while (i < m && books[i] + a <= x) {
          a += books[i];
          i++;
        }
      }
      return i == m;
    });
    stack<int> ans;
    int a = 0;
    int left = k - 1;
    for (int i = m - 1; i >= 0; i--) {
      if (a + books[i] > t || left == i + 1) {
        ans.emplace(0);
        left--;
        a = 0;
      }
      a += books[i];
      ans.emplace(books[i]);
    }
    bool first = true;
    while (!ans.empty()) {
      if (!first) printf(" ");
      first = false;
      int i = ans.top(); ans.pop();
      if (i == 0) {
        printf("/");
      } else {
        printf("%d", i);
      }
    }
    printf("\n");
  }
}
