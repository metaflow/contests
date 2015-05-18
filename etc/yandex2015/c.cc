#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using vllu = vector<llu>;
const int INF = numeric_limits<int>::max();

struct doc {
  int version;
  llu relevance;
  int n;
};

int main() {
  int N;
  cin >> N;
  vllu a(N);
  vector<vllu> docs_values;
  for (int i = 0; i < N; i++) cin >> a[i];
  int D; cin >> D;
  vector<doc> docs;
  auto compare = [] (const doc& a, const doc& b) {
    return a.relevance < b.relevance;
  };
  priority_queue<doc, vector<doc>, decltype(compare)> pq(compare);
  for (int i = 0; i < D; i++) {
    doc d;
    d.relevance = 0;
    d.version = 0;
    vllu values(N);
    d.n = i;
    for (int j = 0; j < N; j++) {
      cin >> values[j];
      d.relevance += a[j] * values[j];
    }
    docs.emplace_back(d);
    docs_values.emplace_back(values);
    pq.push(d);
  }
  int Q; cin >> Q;
  while (Q--) {
    int q_type; cin >> q_type;
    switch(q_type) {
      case 1: {
          int k; cin >> k;
          vector<doc> top;
          while (k > 0 && !pq.empty()) {
            auto d = pq.top(); pq.pop();
            if (docs[d.n].version != d.version) continue;
            top.emplace_back(d);
            k--;
          }
          bool first = true;
          for (auto d : top) {
            if (!first) printf(" ");
            first = false;
            printf("%d", d.n + 1);
            pq.push(d);
          }
          printf("\n");
        }
        break;
      case 2:
        llu d, j, v; cin >> d >> j >> v; d--; j--;
        llu diff = (v - docs_values[d][j]);
        docs[d].relevance += diff * a[j];
        docs_values[d][j] = v;
        docs[d].version++;
        pq.push(docs[d]);
        break;
    }
  }
}
