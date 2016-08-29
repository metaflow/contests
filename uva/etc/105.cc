#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct event {
  bool add;
  int index;
  int x;
};

vector<event> events;
vector<int> heights;
vector<int> heap;
vector<int> heap_index;

void fix_heap(int i) {
  if (i < 1) return;
  int m = heap.size();
  int j = 2 * i;
  if (j >= m) return;
  if (j + 1 < m && heights[heap[j + 1]] > heights[heap[j]]) j++;
  if (heights[heap[i]] >= heights[heap[j]]) return;
  swap(heap[i], heap[j]);
  heap_index[heap[i]] = i;
  heap_index[heap[j]] = j;
  fix_heap(i / 2);
  fix_heap(j);
}

void heap_add(int i) {
  int j = heap.size();
  heap.emplace_back(i);
  heap_index[heap[j]] = j;
  fix_heap(j / 2);
}

void heap_delete(int i) {
  int j = heap_index[i];
  int e = heap.size() - 1;
  heap[j] = heap[e];
  heap_index[heap[j]] = j;
  heap.resize(e);
  fix_heap(j);
}

int get_max() {
  if (heap.size() < 2) return 0;
  return heights[heap[1]];
}

int main() {
  int l, h, r;
  while (cin >> l >> h >> r) {
    int i = heights.size();
    heights.emplace_back(h);
    events.emplace_back(event{true, i, l});
    events.emplace_back(event{false, i, r});
  }
  heap_index.resize(heights.size());
  sort(events.begin(), events.end(), [] (const event & a, const event & b) {
    return a.x < b.x;
  });
  int last_max = 0;
  bool first = true;
  heap.emplace_back(-1);
  for (size_t i = 0; i < events.size();) {
    int x = events[i].x;
    cerr << x << endl;
    while (i < events.size() && events[i].x == x) {
      if (events[i].add) {
        heap_add(events[i].index);
      } else {
        heap_delete(events[i].index);
      }
      i++;
    }
    int m = get_max();
    if (m == last_max) continue;
    last_max = m;
    if (!first) printf(" "); first = false;
    printf("%d %d", x, m);
  }
  printf("\n");
}
