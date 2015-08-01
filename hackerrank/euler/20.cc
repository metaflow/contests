#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

template <typename Iterator>
ostream& print_range(ostream& s, const Iterator a, const Iterator b) {
  bool first = true;
  for (auto i = a; i != b; i++) {
    if (!first) s << " ";
    first = false;
    s << *i;
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  vvi digits(1001);
  digits[0].push_back(1);
  for (int i = 1; i < 1001; i++) {
    int j = 0;
    while (j < digits[i - 1].size() && digits[i - 1][j] == 0) j++;
    while (j < digits[i - 1].size()) {
      digits[i].emplace_back(digits[i - 1][j] * i);
      j++;
    }
    for (j = 0; j < digits[i].size() - 1; j++) {
      if (digits[i][j] >= 10) {
        digits[i][j + 1] += digits[i][j] / 10;
        digits[i][j] %= 10;
      }
    }
    while (digits[i].back() >= 10) {
      int t = digits[i].back();
      digits[i].back() = t % 10;
      digits[i].emplace_back(t / 10);
    }
  }

  vi sum(1001);
  for (int i = 0; i < 1001; i++) {
    for (auto a : digits[i]) sum[i] += a;
  }

  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << sum[n] << endl;
  }
}
