#include <vector>
#include <iostream>

using namespace std;

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int p;
        cin >> p;
        vector<int> c;
        for (int i = 0; i <= p; i++) {
            int v;
            cin >> v;
            c.push_back(v);
        }
        int k, d;
        cin >> d >> k;
        long long b = 0;
        int n = 0;
        for (int i = 1; i <= k; i++) {
            n += i * d;
            if (n >= k) {
                while (!c.empty()) {
                    b = b * i + c.back();
                    c.pop_back();
                }
                break;
            }
        }
        printf("%lld\n", b);
    }
    return 0;
}
