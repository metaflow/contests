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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const ll MAX = 10000001;

ll distinct[MAX];

const ll MAX_PRIME = 10000001;
void sieve_primes() {
  for (ll i = 2; i <= MAX_PRIME; i++) {
    if (distinct[i]) continue;
    // primes.emplace_back(i);
    for (ll j = i; j <= MAX_PRIME; j += i) distinct[j]++;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  fill(&distinct[0], &distinct[MAX], 0);
  sieve_primes();
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll a, b, k;
    cin >> a >> b >> k;
    ll answer = 0;
    for (ll i = a; i <= b; i++) {
      if (distinct[i] == k) answer++;
    }
    cout << "Case #" << tc << ": " << answer << endl;
  }
}
