#include <vector>
#include <iostream>

using namespace std;

void collapse(vector<int> &t) {
    for (int i = 0; i + 2 < t.size(); i++) {
        int a = t[i];
        if (a == t[i + 1] && a == t[i + 2]) {
            while (i < t.size() && t[i] == a) {
                t.erase(t.begin() + i);
            }
            collapse(t);
            return;
        }
    }
}

int main() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> balls;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        balls.push_back(v);
    }
    int m = 0;
    for (int i = 1; i < n; i++) {
        if ((balls[i - 1] == x) &&
            (balls[i] == x) &&
            ((i == 1) || (balls[i - 2] != x))) {
            vector<int> t(balls);
            t.insert(t.begin() + i, x);
            collapse(t);
            int d = balls.size() - t.size();
            m = max(m, d);
        }
    }
    cout << m << endl;
}
