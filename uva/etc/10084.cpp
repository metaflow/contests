#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;

struct point { double x, y; };
struct v { point a, d; };

int sign(double a) {
  if (a == 0) return 0;
  if (a < 0) return -1;
  return 1;
}

v get_median(point a, point b) {
  v r;
  r.a.x = (a.x + b.x) / 2;
  r.a.y = (a.y + b.y) / 2;
  point da;
  da.x = b.x - a.x;
  da.y = b.y - a.y;
  if (da.y == 0) {
    r.d.x = 0;
    r.d.y = -sign(da.x);
  } else {
    r.d.x = sign(da.y);
    r.d.y = -da.x * r.d.x / da.y;
  }
  return r;
}

double vmult(point a, point b) { // vector multiplication
  return a.x * b.y - b.x * a.y;
}

point line_intersect(v m, point a, point b) {
  point r;
  v n;
  n.a = a;
  n.d.x = b.x - a.x;
  n.d.y = b.y - a.y;
  if (m.d.x == 0) {
    r.x = m.a.x;
    double an = n.d.y / n.d.x;
    double bn = n.a.y - an * n.a.x;
    r.y = an * r.x + bn;
  } else {
    double am = m.d.y / m.d.x;
    double bm = m.a.y - am * m.a.x;
    if (n.d.x == 0) {
      r.x = n.a.x;
    } else {
      double an = n.d.y / n.d.x;
      double bn = n.a.y - an * n.a.x;
      r.x = - (bm - bn) / (am - an);
    }
    r.y = am * r.x + bm;
  } 
  return r;
}

vector<point> intersect(vector<point> g, v m, int d) {
  vector<point> r;
  point b;
  b.x = g[g.size() - 1].x - m.a.x;
  b.y = g[g.size() - 1].y - m.a.y;
  int ld = sign(vmult(m.d, b));
  for (int i = 0; i < g.size(); i++) {
    b.x = g[i].x - m.a.x;
    b.y = g[i].y - m.a.y;
    int t = sign(vmult(m.d, b));
    if (t == 0) {
      r.push_back(g[i]);
    } else {
      if (ld != t && ld != 0) {
        point p = line_intersect(m, g[(i - 1 + g.size()) % g.size()], g[i]);
        r.push_back(p);
      }
      if (t == d) r.push_back(g[i]);
    }
    ld = t;
  }
  return r;
}

double get_area(vector<point> g) {
  double r = 0;
  int n = g.size();
  for (int i = 1; i < n - 1; i++) {
    int j = i + 1;
    point a, b;
    a.x = g[i].x - g[0].x;
    a.y = g[i].y - g[0].y;
    b.x = g[j].x - g[0].x;
    b.y = g[j].y - g[0].y;
    r += vmult(a, b);
  }
  return r / 2;
}

void process(vector<point> pp, vector<int> dd) {
  point p;
  p.x = 0;
  p.y = 0;
  vector<point> g;
  g.push_back(p);
  p.x = 10;
  g.push_back(p);
  p.y = 10;
  g.push_back(p);
  p.x = 0;
  g.push_back(p);
  point last;
  last.x = 0;
  last.y = 0;
  double s = 100;
  for (int i = 0; i < pp.size(); i++) {
    if (s > 0) {
      int d = dd[i];
      p = pp[i];
      if (d == 0) {
        if (p.x != last.x || p.y != last.y) s = 0;
      } else {
        if (p.x == last.x && p.y == last.y) {
          s = 0;
        } else {
          v m = get_median(last, p);        
          g = intersect(g, m, d);
          s = get_area(g);
          last = p;  
        }        
      }
    }
    printf("%.2lf\n", s);
  }
} 

int main() {
  point p;
  char s[80];
  vector<point> pp; 
  vector<int> dd;
  while(scanf("%lf%lf%s", &(p.x), &(p.y), s) != EOF) {
    int d = 0;
    switch(s[0]) {
      case 'H': d = 1; break;
      case 'C': d = -1; break;
    }
    pp.push_back(p);
    dd.push_back(d);
  }
  process(pp, dd);
  return 0;
}
