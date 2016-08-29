#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const int MAX = 5000001;
int cumulative[MAX];

void sieve() {
  vi sum(MAX);
  fill_n(cumulative, MAX, 0);
  for (int i = 2; i < MAX; i++) {
    cumulative[i] = cumulative[i - 1];
    if (sum[i]) {
      if (sum[sum[i]] == 0) cumulative[i]++;
      continue;
    }
    cumulative[i]++;
    for (ll j = 2; j * i < MAX; j++) sum[i * j] += i;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  sieve();
  int a, b;
  while (cin >> a, a) {
    cin >> b;
    cout << cumulative[b] - cumulative[a - 1] << endl;
  }
}
