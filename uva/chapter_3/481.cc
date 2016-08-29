#include <vector>
#include <iostream>
#include <stack>

using namespace std;

int main() {
    vector<int> a;
    int v;
    while (cin >> v) a.push_back(v);
    vector<int> l;
    vector<int> lr;
    vector<int> ref(a.size());
    int best_i = -1;
    for (int i = 0; i < a.size(); i++) {
        auto it = lower_bound(l.begin(), l.end(), a[i]);
        if (it == l.end()) {
            l.push_back(a[i]);
            best_i = i;
            ref[i] = lr.empty() ? -1 : lr.back();
            lr.push_back(i);
            continue;
        }
        if (it == l.end() - 1) {
            ref[i] = lr.size() <= 1 ? -1 : lr[lr.size() - 2];;
            best_i = i;
        }
        if (a[i] < *it) {
            *it = a[i];
            int p = it - l.begin();
            lr[p] = i;
            ref[i] = p == 0 ? -1 : lr[p-1];
        }
    }
    printf("%lu\n-\n", l.size());
    stack<int> s;

    while (best_i != -1) {
        s.push(a[best_i]);
        best_i = ref[best_i];
    }

    while (!s.empty()) {
        printf("%d\n", s.top());
        s.pop();
    }

}
