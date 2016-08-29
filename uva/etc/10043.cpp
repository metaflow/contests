#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct point { int x, y; };

bool cmpx(point const a, point const b) { return a.x < b.x; }
bool cmpy(point const a, point const b) { return a.y < b.y; }

void add_points(vector<point> &pp, int l) {
  sort(pp.begin(), pp.end(), cmpx);
  int s = pp.size(); 
  point p;
  p.x = 0;
  p.y = 0;
  pp.push_back(p);  
  for (int i = 0; i < s; i++) {
    if (pp[i].x == p.x) continue;
    p.x = pp[i].x;
    pp.push_back(p);
    p.x++;
    if (p.x > l) break;
    pp.push_back(p);
  }
  if (p.x < l) {
    p.x = l;
    pp.push_back(p);
  }
}

int find_for(point p, vector<point> &pp, int l, int w, int f) {
  int xl = 0;
  int xr = l;
  int r = 0;
  for (int i = f; i < pp.size(); i++) {
    if (pp[i].y <= p.y) continue;
    int x = pp[i].x;
    if (x <= xl || x >= xr) continue;
    int s = (xr - xl) * (pp[i].y - p.y);
    if (s > r) r = s;
    if (x <= p.x) xl = x;
    if (x >= p.x) xr = x;
    if (x == p.x) break;
  }
  int s = (xr - xl) * (w - p.y);
  if (s > r) r = s;
  return r;
}

int solve(vector<point> &pp, int l, int w) {
  int r = 0;
  add_points(pp, l);
  sort(pp.begin(), pp.end(), cmpy);
  for (int i = 0; i < pp.size(); i++) {
    int t = find_for(pp[i], pp, l, w, i + 1);
    if (t > r) r = t;
  }
  return r;
}

int main() {
  int cases;
  scanf("%d", &cases);
  for (int c = 0; c < cases; c++) {
    int l, w;
    scanf("%d%d", &l, &w);
    vector<point> pp;
    while (true) {
      int k, x, y, dx, dy;
      dx = 0;
      dy = 0;
      scanf("%d", &k);
      // cerr << "k " << k << "\n";
      if (k == 0) break;
      scanf("%d%d", &x, &y);
      if (k != 1) scanf("%d%d", &dx, &dy);
      for (int i = 0; i < k; i++) {
        point p;
        p.x = x;
        p.y = y;
        x += dx;
        y += dy;
        pp.push_back(p);
      }
    }
    int s = solve(pp, l, w);
    printf("%d\n", s);
  }
  return 0;
}
