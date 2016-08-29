#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vi primes;

void prepare_primes() {
  bitset<101> b;
  b.reset();
  for (int i = 2; i < 100; i++) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (int j = i * i; j < 100; j += i) b[j] = true;
  }
}

int main() {
  prepare_primes();
  vector<vector<int>> factorization(101);

  for (int i = 1; i <= 100; i++) {
    int j = i;
    factorization[i].resize(primes.size(), 0);
    if (i == 1) continue;
    for (llu k = 0; k < primes.size(); k++) {
      factorization[i][k] = factorization[i - 1][k];
      while (j % primes[k] == 0) {
        j /= primes[k];
        factorization[i][k]++;
      }
    }
  }
  int n;
  while (cin >> n, n) {
    printf("%3d! =", n);
    for (llu i = 0; i < factorization[n].size(); i++) {
      if (factorization[n][i] == 0) break;
      if (i == 15) printf("\n      ");
      printf("%3d", factorization[n][i]);
    }
    printf("\n");
  }
}
