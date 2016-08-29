#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vector<vector<int>> reps;
vi primes = {2, 3, 5, 7, 11, 13, 17, 19};

void init_reps() {
  for (int i = 0; i < 21; i++) {
    vi r(primes.size());
    int t = i;
    for (size_t j = 0; j < primes.size(); j++) {
      if (i < 2) break;
      r[j] += reps[i - 1][j];
      while (t % primes[j] == 0) {
        t /= primes[j];
        r[j]++;
      }
    }
    reps.emplace_back(r);
  }
}

int main() {
  int tcc;
  cin >> tcc;
  init_reps();
  for (int tc = 1; tc <= tcc; tc++) {
    string s;
    cin >> s;
    vector<int> counts(26);
    for (auto c : s) counts[c - 'A']++;
    vector<int> p = reps[s.size()];
    for (auto i : counts) {
      for (size_t j = 0; j < primes.size(); j++) {
        p[j] -= reps[i][j];
      }
    }
    llu n = 1;
    for (size_t j = 0; j < primes.size(); j++) {
      n *= pow(primes[j], p[j]);
    }
    printf("Data set %d: %llu\n", tc, n);
  }
}
