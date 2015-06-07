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

namespace sum_all {
  bool __data_ready = false;
  int n;
  vector<int> v;

  void read_data() {
    if (__data_ready) return;
    __data_ready = true;
    std::ifstream f("in.dat");
    f >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) f >> v[i];
  }  
}


int GetN() { sum_all::read_data(); return sum_all::n; }

int GetNumber(int p) { sum_all::read_data(); return sum_all::v[p]; }
