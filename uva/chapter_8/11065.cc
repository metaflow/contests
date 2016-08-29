#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 61;

llu M[MAX];

int vertices_count;
llu all;
llu sets_count;
int max_set_size;

void backtrack(int from, llu used, int size) {
  if (used == all) {
    sets_count++;
    max_set_size = max(max_set_size, size);
    return;
  }
  for (int i = from; i < vertices_count; i++) {
    if (used & (1llu << i)) continue;
    backtrack(i + 1, used | M[i], size + 1);
  }
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int edges_count;
    cin >> vertices_count >> edges_count;
    fill_n(M, MAX, 0);
    for (int i = 0; i < vertices_count; i++) M[i] = (1llu << i);
    while (edges_count--) {
      int a, b; cin >> a >> b;
      M[a] = M[a] | (1llu << b);
      M[b] = M[b] | (1llu << a);
    }
    max_set_size = 0;
    sets_count = 0;
    all = (1llu << vertices_count) - 1;
    backtrack(0, 0, 0);
    cout << sets_count << endl << max_set_size << endl;
  }
}
