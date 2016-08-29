#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Big {
    vector<int> c;
    bool n;
public:
    Big(int v) {
        set(v);
    }

    Big(const Big& a) {
        c = a.c;
        n = a.n;
    }

    void set(int v) {
        n = v < 0;
        c.clear();
        c.push_back(abs(v));
    }

    bool operator < (const Big& a) const {
        if (n != a.n) return n;
        if (c.size() != a.c.size()) return c.size() < a.c.size();
        for (int i = c.size() - 1; i >= 0; i--) {
            if (c[i] != a.c[i]) return c[i] < a.c[i];
        }
        return false;
    }

    void mult(int a) {
        n = (n ^ (a < 0)) && (a != 0);
        a = abs(a);
        for (auto &t : c) {
            t *= a;
        }
        for (int i = 0; i < c.size() - 1; i++) {
            c[i + 1] += c[i] / 1000;
            c[i] %= 1000;
        }
        while (c.back() >= 1000) {
            int t = c.back();
            c.back() = t % 1000;
            c.push_back(t / 1000);
        }
        while (c.size() > 1 && c.back() == 0) c.erase(c.end() - 1);
    }

    void print() {
        if (n) putchar('-');
        printf("%d", c.back());
        for (int i = c.size() - 2; i >= 0; i--) {
            printf("%03d", c[i]);
        }
    }
};



int main() {
    long long v[200];
    while (scanf("%lld", v) == 1) {
        int n = 1;
        while (true) {
            scanf("%lld", v + n);
            if (v[n] == -999999) break;
            n++;
        }
        Big m(v[0]);
        Big p(1);
        for (int i = 0; i < n; i++) {
            p.mult(v[i]);
            // p.print(); printf("...\n");
            m = max(m, p);
            if (v[i] == 0) p.set(1);
        }
        p.set(1);
        for (int i = n - 1; i >= 0; i--) {
            p.mult(v[i]);
            m = max(m, p);
            if (v[i] == 0) p.set(1);
        }
        m.print();
        printf("\n");
    }
}
