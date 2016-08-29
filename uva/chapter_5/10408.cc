#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

ii faray(int n, int k) {
  auto cmp = [] (const ii &a, const ii &b) {
    return a.first * b.second > b.first * a.second;
  };
  priority_queue<ii, vector<ii>, decltype(cmp)> pq(cmp);
  for (int i = 1; i <= n; i++) pq.emplace(1, i);
  for (int i = 0; i < k - 1; i++) {
    auto e = pq.top(); pq.pop();
    e.first++;
    while (e.first < e.second && gcd(e.first, e.second) != 1) e.first++;
    if (e.first != e.second) pq.emplace(e);
  }
  return pq.top();
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    auto p = faray(n, k);
    printf("%d/%d\n", p.first, p.second);
  }
}
