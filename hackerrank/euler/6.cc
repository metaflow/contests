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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  vll answer;
  ll sum = 0, sum_squares = 0;
  for (int i = 0; i <= 10000; i++) {
    sum += i;
    sum_squares += i * i;
    answer.emplace_back(sum * sum - sum_squares);
  }

  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << answer[n] << endl;
  }
}
