#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1005;

string s;
size_t sa[MAX], ra[MAX], lcp[MAX];

void count_sort(size_t k) {
  vi counts(max(s.size(), (size_t)300));
  size_t sa_[MAX];
  for (size_t i = 0; i < s.size(); i++) {
    if (i + k >= s.size()) {
      counts[0]++;
    } else {
      counts[ra[i + k]]++;
    }
  }
  int sum = 0;
  for (size_t i = 0; i < counts.size(); i++) {
    int t = counts[i];
    counts[i] = sum;
    sum += t;
  }

  for (size_t i = 0; i < s.size(); i++) {
    int p = 0;
    if (sa[i] + k < s.size()) p = ra[sa[i] + k];
    sa_[counts[p]] = sa[i];
    counts[p]++;
  }

  swap(sa, sa_);
}

void build_sa() {
  for (size_t i = 0; i < s.size(); i++) {
    sa[i] = i;
    ra[i] = s[i];
  }
  size_t ra_[MAX];
  for (size_t k = 1; k < s.size(); k <<= 1) {
    count_sort(k);
    count_sort(0);
    int r = 0;
    ra_[sa[0]] = 0;
    for (size_t i = 1; i < s.size(); i++) {
      if (ra[sa[i - 1]] != ra[sa[i]]
        || ra[sa[i - 1] + k] != ra[sa[i] + k]) r++;
      ra_[sa[i]] = r;
    }
    if (ra_[s.size() - 1] + 1 == s.size()) break;
    swap(ra, ra_);
  }
}

void build_lcp() {
  int p[MAX];
  p[sa[0]] = -1;
  for (size_t i = 1; i < s.size(); i++) p[sa[i]] = sa[i - 1];
  size_t plcp[MAX];
  int u = 0;
  for (size_t i = 0; i < s.size(); i++) {
    if (p[i] == -1) { plcp[i] = u = 0; continue; }
    while (s[i + u] == s[p[i] + u]) u++;
    plcp[i] = u;
    u--;
    if (u < 0) u = 0;
  }
  for (size_t i = 0; i < s.size(); i++) lcp[i] = plcp[sa[i]];
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    cin >> s;
    s += '#';
    build_sa();
    build_lcp();
    size_t j = 0;
    for (size_t i = 1; i < s.size(); i++) {
      if (lcp[j] < lcp[i]) j = i;
    }
    if (lcp[j] == 0) {
      printf("No repetitions found!\n");
    } else {
      int c = 1;
      for (size_t i = j; i < s.size(); i++, c++) {
        if (lcp[j] != lcp[i]) break;
      }
      printf("%s %d\n", s.substr(sa[j], lcp[j]).c_str(), c);
    }
  }
}
