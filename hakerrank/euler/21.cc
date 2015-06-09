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

const int MAX = 100001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vi sum(MAX);
  for (ll i = 1; i < MAX; i++) {
    for (ll j =  2 * i; j < MAX; j += i) sum[j] += i;
  }
  vll answer(MAX);
  for (int i = 0; i < MAX - 1; i++) {
    answer[i + 1] = answer[i];
    int j = sum[i];
    if (i != j && j < MAX && sum[j] == i) {
      answer[i + 1] += i;
    }
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << answer[n] << endl;
  }
}
