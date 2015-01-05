#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll f(ll n) {
  if (n % 2 == 0) return n / 2;
  return f(n - 1) - n;
}

int main() {
  ll n;
  while (cin >> n) {
    cout << f(n) << endl;
  }
}
