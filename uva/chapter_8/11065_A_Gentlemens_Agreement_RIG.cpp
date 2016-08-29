#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 61;

default_random_engine source(random_device{}());
uniform_real_distribution<double> one(0, 1);


void print_graph(int size) {  
  double density = one(source);  
  llu M[MAX];  
  vi connected;
  vi disconnected;
  for (int i = 1; i < size; i++) disconnected.emplace_back(i);
  int roads = 0;
  connected.emplace_back(0);
  fill_n(M, MAX, 0);
  // make connected
  while (!disconnected.empty()) {
    uniform_int_distribution<> a(0, connected.size() - 1);
    uniform_int_distribution<> b(0, disconnected.size() - 1);
    int i = connected[a(source)];
    auto p = disconnected.begin() + b(source);
    M[i] = M[i] | (1llu << (*p));
    M[*p] = M[*p] | (1llu << i);
    roads++;
    connected.emplace_back(*p);
    disconnected.erase(p);
  }
  // add random edges
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (one(source) < density) {
        if (M[i] & (1llu << j)) continue;
        M[i] = M[i] | (1llu << j);
        // M[j] = M[j] | (1 << i);
        roads++;
      }
    }
  }

  printf("%d %d\n", size, roads);
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (M[i] & (1llu << j)) printf("%d %d\n", i, j);
    }
  }

  // printf("\n");
}

int main() {
  int cases = 5;
  printf("%d\n", cases);
  print_graph(1);
  uniform_int_distribution<> size(1, MAX - 1);
  for (int i = 0; i < cases - 2; i++) {
    print_graph(size(source));
  }
  print_graph(MAX - 1);
}
