#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;


// v max flow
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  int age;
  vector<pedge> adjusted;
  pedge back, to_sink;
  l size;
};

struct edge {
  pnode from, to;
  l flow, original_flow;
  pedge opposite;
};

l adjust(pedge e, l d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

pedge connect(pnode &a, pnode &b, l w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->flow = w; ea->opposite = eb;
  ea->original_flow = ea->flow;
  eb->from = b; eb->to = a; eb->flow = 0; eb->opposite = ea;
  eb->original_flow = eb->flow;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
  return ea;
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
  int result = 0;
  while (true) {
    for (auto u : g) u->age = 0;
    queue<pnode> q;
    q.push(source); source->age = 1;
    while (!(q.empty() || sink->age != 0)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->age != 0 || e->flow == 0) continue;
        v->back = e;
        v->age = u->age + 1;
        q.push(v);
      }
    }
    if (sink->age == 0) break;
    for (auto e : sink->adjusted) {
      auto o = e->opposite;
      if (o->from->age != sink->age - 1 || o->flow == 0) continue;
      result += adjust(o, o->flow);
    }
  }
  return result;
}
// ^ max flow

// invariant: answer is within (a, b], f(a) = false, f(b) = true
l binary_search_lower(l a, l b, function<bool(l)> f) {
  while (b - a > 1) {
    l m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

class FleetFunding {
    public:
    int maxShips(int m, vector <int> k, vector <int> a, vector <int> b) {
      l n = k.size();
      graph g(n);
      for (auto &u : g) u = make_shared<node>();
      vector<ii> events;
      for (l i = 0; i < n; i++) {
        events.emplace_back(a[i] - 1, i);
        events.emplace_back(b[i], i);
      }
      events.emplace_back(INF, 0);
      sort(events.begin(), events.end());
      vb started(n);
      l i = -1, j = 1;
      vl to_add, to_remove;
      for (auto e : events) {
        if (e.first != i) {
          // if anything is active create new target [j, i]
          // and update started from to_add, to_remove
          if (i >= j) {
            pnode u = make_shared<node>();
            g.emplace_back(u);
            u->size = i - j + 1;
            for (l e = 0; e < n; e++) {
              if (!started[e]) continue;
              connect(g[e], u, INF);
              // cerr << e << " -> " << j << ".." << i << endl;
            }
          }
          for (auto e : to_add) started[e] = true;
          for (auto e : to_remove) started[e] = false;
          to_add.clear();
          to_remove.clear();
          j = i + 1;
          i = e.first;
        }
        if (started[e.second]) {
          to_remove.emplace_back(e.second);
        } else {
          to_add.emplace_back(e.second);
        }
      }
      pnode source = make_shared<node>();
      pnode sink = make_shared<node>();

      for (l i = 0; i < n; i++) {
        connect(source, g[i], k[i]);
      }
      for (l i = n; i < g.size(); i++) {
        g[i]->to_sink = connect(g[i], sink, 0);
      }
      g.emplace_back(source);
      g.emplace_back(sink);
      l max_k = 0;
      for (l i : k) max_k = max(max_k, i);
      l remove = binary_search_lower(-1, max_k, [&](l remove) {
        for (auto u : g) {
          for (auto e : u->adjusted) {
            e->flow = e->original_flow;
          }
        }
        l left = max_k - remove;
        for (l i = n; i < g.size(); i++) {
          g[i]->to_sink->flow = g[i]->size * left;
        }
        return max_flow(g, source, sink) == n * left;
      });
      return max_k - remove;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arr1[] = {2,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,3,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(0, Arg4, maxShips(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arr1[] = {10,9,8,7,6,5,4,3,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,1,1,1,1,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,1,1,1,1,1,1,1,1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 55; verify_case(1, Arg4, maxShips(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; int Arr1[] = {2,4,6,8,10,1,3,5,7,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(2, Arg4, maxShips(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 84457; int Arr1[] = {374778,169109,529984,498638,29462,465769,29285,394948,307944,459189,
349316,766627,686851,404285,850199,359378,3014,248257,558856,27393,32370,
574862,337134,965567,32223,935678,389898,973497,990575,483190,122899,
857994,991217,149619,415870}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {92,4997,11,28545,933,210,2,124,114,4513,32959,1,57,17,13,133,1843,41851,
3,9296,9757,28,3,769,10,11102,683,6173,11821,3982,214,2,4304,439,1998}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {81034,54474,70239,79597,47317,82938,83883,74652,84033,84422,84456,84457,
81095,83743,79210,84255,84455,45596,84456,82959,67062,80330,44090,84445,
84454,84450,45931,77190,83025,83567,83639,84333,83355,70982,84456}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 186; verify_case(3, Arg4, maxShips(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 2; int Arr1[] = {1000000,1000000,1000000,1000000,1000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,2,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,1,2,2,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2500000; verify_case(4, Arg4, maxShips(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    FleetFunding ___test;
    ___test.run_test(-1);
}
// END CUT HERE
