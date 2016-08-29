#include <cmath>
#include <stdio.h>
#include <iostream>

using namespace std;

int p, q, r, s, t, u;

double f(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

double fd(double x){ // the derivative of function f
  return -p*exp(-x) + q*cos(x) - r*sin(x) + s/(cos(x)*cos(x)) + 2*t*x;
}

int loops = 0;

const double EPS = 1e-7;

double newton(){
  if (f(0)==0) return 0;
  for (double x=0.5; ;){             // initial guess x = 0.5
    loops++;
    double x1 = x - f(x)/fd(x);      // x1 = next guess
    if (round(x1 * 10000) == round(x * 10000)) return x;
    x = x1;
  }
}

int main() {
    while (scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) == 6) {
        double r = 1.0d;
        double l = 0.0d;
        double lv = f(l);
        double rv = f(r);
        if (lv * rv > 0) {
            printf("No solution\n");
            continue;
        }
        printf("%.4lf\n", newton());
    }
    cerr << loops;
    return 0;
}
